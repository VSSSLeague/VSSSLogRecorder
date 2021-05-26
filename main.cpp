#include <QCoreApplication>
#include <QCommandLineParser>
#include <src/utils/exithandler/exithandler.h>
#include <src/recorder/recorder.h>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    a.setApplicationName(APP_NAME);
    a.setApplicationVersion(APP_VERSION);

    // Setup command line parser
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    // Setup application options
    // File name
    QCommandLineOption fileName("fileName",
                                 QCoreApplication::translate("main", "Set desired log fileName (e.g.: 2020-04-01_match)"),
                                 QCoreApplication::translate("main", "fileName"));
    parser.addOption(fileName);

    // Vision network
    QCommandLineOption visionNetwork("vision",
                                 QCoreApplication::translate("main", "Set vision address:port (default is 224.0.0.1:10002)"),
                                 QCoreApplication::translate("main", "address>:<port"));
    parser.addOption(visionNetwork);

    // Referee network
    QCommandLineOption refereeNetwork("referee",
                                 QCoreApplication::translate("main", "Set referee address:port (default is 224.5.23.2:10003)"),
                                 QCoreApplication::translate("main", "address>:<port"));
    parser.addOption(refereeNetwork);

    // Process parser in application
    parser.process(a);

    // Setup ExitHandler
    ExitHandler::setApplication(&a);
    ExitHandler::setup();

    // Parse
    // File Name
    QString logFileName = Timer::getActualTime() + ".log";
    if(parser.isSet(fileName)) {
        logFileName = parser.value(fileName) + ".log";
    }

    // Vision
    QString visionAddress = "224.0.0.1";
    quint16 visionPort = 10002;
    if(parser.isSet(visionNetwork)) {
        QString visionNetworkValue = parser.value(visionNetwork);
        visionAddress = visionNetworkValue.split(":").at(0);
        visionPort = visionNetworkValue.split(":").at(1).toUInt();
    }

    // Referee
    QString refereeAddress = "224.5.23.2";
    quint16 refereePort = 10003;
    if(parser.isSet(refereeNetwork)) {
        QString refereeNetworkValue = parser.value(refereeNetwork);
        refereeAddress = refereeNetworkValue.split(":").at(0);
        refereePort = refereeNetworkValue.split(":").at(1).toUInt();
    }

    // Create recorder
    Recorder *recorder = new Recorder(logFileName, visionAddress, visionPort, refereeAddress, refereePort);

    // Wait for main program end
    int exec = a.exec();

    // Delete recorder
    delete recorder;

    return exec;
}
