#include <QApplication>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QPushButton* button = new QPushButton("Click");
    QSpinBox* spinBox = new QSpinBox();
    QSlider* slider = new QSlider(Qt::Horizontal);

    spinBox->setMaximum(100);
    slider->setMaximum(100);

    QWidget* window = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout();

    layout->addWidget(button);
    layout->addWidget(spinBox);
    layout->addWidget(slider);
    window->setLayout(layout);
    window->show();

    QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

    return app.exec();
}
