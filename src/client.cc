#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>


class client
{
public:
  client(boost::asio::io_service& io_service, boost::asio::ssl::context& context, boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
    : socket_(io_service, context)
  {
    // socket_.set_verify_mode(boost::asio::ssl::context::verify_none);
    socket_.set_verify_callback(boost::bind(&client::verify_certificate, this, _1, _2));

    boost::asio::async_connect(socket_.lowest_layer(), endpoint_iterator, boost::bind(&client::handle_connect, this, boost::asio::placeholders::error));
  }

  bool verify_certificate(bool preverified, boost::asio::ssl::verify_context& ctx)
  {
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
    std::cout << "Verifying:\n" << subject_name << std::endl;

    return preverified;
  }

  void handle_connect(const boost::system::error_code& error)
  {
    if(!error){
      std::cout << "Connection OK!" << std::endl;
      socket_.async_handshake(boost::asio::ssl::stream_base::client, boost::bind(&client::handle_handshake, this, boost::asio::placeholders::error));
    }else{
      std::cout << "Connect failed: " << error.message() << std::endl;
    }
  }

  void handle_handshake(const boost::system::error_code& error)
  {
    if(!error){
      std::cout << "Sending request: " << std::endl;

      std::stringstream request_;

// 0000: GET /tracks?client_id=a5a98f5d549a83896d565f69eb644b65&limit=10
//  99 0040: HTTP/1.1
// 100 004a: User-Agent: curl/7.32.0
// 101 0063: Host: api.soundcloud.com
// 102 007d: Accept: */*
// 103 008a:


      request_ << "GET /tracks?client_id=a5a98f5d549a83896d565f69eb644b65&limit=10 HTTP/1.1\r\n";
      // request_ << "HTTP/1.1";

      request_ << "User-Agent: curl/7.32.0\r\n";
      request_ << "Host: api.soundcloud.com\r\n";

      request_ << "Accept: */*\r\n";
      request_ << "Connection: close\r\n";

      // request_ << "Accept-Encoding: *\r\n";
      request_ << "\r\n";

      std::cout << request_.str() << std::endl;

      boost::asio::async_write(socket_, boost::asio::buffer(request_.str()), boost::bind(&client::handle_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }else{
      std::cout << "Handshake failed: " << error.message() << std::endl;
    }
  }

  void handle_write(const boost::system::error_code& error, size_t bytes_transferred)
  {
    if (!error){
      std::cout << "Sending request OK!" << std::endl;
      boost::asio::async_read(socket_, boost::asio::buffer(reply_, bytes_transferred), boost::bind(&client::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }else{
      std::cout << "Write failed: " << error.message() << std::endl;
    }
  }

  void handle_read(const boost::system::error_code& error, size_t bytes_transferred)
  {
    if (!error){
      std::cout << "Reply: ";
      std::cout.write(reply_, bytes_transferred);
      std::cout << "\n";
    }else{
      std::cout << "Read failed: " << error.message() << std::endl;
    }
  }

private:
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
  char reply_[0x1 << 18];
};

int main(int argc, char* argv[])
{
  try{
    boost::asio::io_service io_service;

    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query("api.soundcloud.com", "443");
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

    boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
    context.set_default_verify_paths();

    client c(io_service, context, iterator);

    io_service.run();
  }catch (std::exception& e){
    std::cerr << "Exception: " << e.what() << "\n";
  }

  std::cin.get();
  return 0;
}
