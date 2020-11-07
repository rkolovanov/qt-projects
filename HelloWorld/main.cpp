#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QLabel label("Hello, Universe!");

    label.show();

    return app.exec();
}
