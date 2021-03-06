#include "examples/http_server/TimeHttpPage.hpp"
#include "services/network_win/ConnectionWin.hpp"
#include "hal/windows/TimerServiceWin.hpp"
#include "services/network/HttpServer.hpp"
#include "services/network_win/EventDispatcherWithNetwork.hpp"

int main(int argc, const char* argv[], const char* env[])
{
    services::EventDispatcherWithNetwork eventDispatcherWithNetwork;
    hal::TimerServiceWin timerService;

    services::DefaultHttpServer::WithBuffer<2048> httpServer(eventDispatcherWithNetwork, 80);
    application::TimeHttpPage timePage;
    httpServer.AddPage(timePage);

    eventDispatcherWithNetwork.Run();
}
