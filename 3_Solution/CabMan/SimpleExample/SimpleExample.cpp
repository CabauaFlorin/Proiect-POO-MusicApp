#include <iostream>

#ifdef _WIN32
#define _WIN32_WINNT 0X0A00
#endif
#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
using namespace std;

vector <char> vBuffer(20 * 1024);

void GrabSomeData(asio::ip::tcp::socket& socket)
{
	socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()), [&](error_code ec, size_t lenght)
		{
			if (!ec)
			{
				cout << "\n\nRead " << lenght << " bytes\n\n";

				for (int i = 0; i < lenght; i++)
					cout << vBuffer[i];

				GrabSomeData(socket);
			}
		}
	);
}

int main()
{
	asio::error_code ec;

	asio::io_context context;

	asio::io_context::work idleWork(context);

	thread thrContext = thread([&]() {context.run(); });

	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);

	asio::ip::tcp::socket socket(context);

	socket.connect(endpoint, ec);

	if (!ec)
	{
		cout << "Connected!" << endl;
	}
	else
	{
		cout << "Failed to connect to adress:\n" << ec.message() << endl;
	}

	if (socket.is_open())
	{
		GrabSomeData(socket);

		string sRequest =
			"GET /index.html HTTP/1.1\r\n"
			"Host: example.com\r\n"
			"Connection: close\r\n\r\n";

		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

		using namespace chrono_literals;
		this_thread::sleep_for(200ms);

		context.stop();
		if (thrContext.joinable()) thrContext.join();

		//socket.wait(socket.wait_read);

		//size_t bytes = socket.available();
		//cout << "Bytes Available: " << bytes << endl;

		//if (bytes > 0)
		//{
		//	vector <char> vBuffer(bytes);
		//	socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);

		//	for (auto c : vBuffer)
		//	{
		//		cout << c;
		//	}
		//}

		//GrabSomeData(socket);
	}

	//system("pause");
	return 0;
}