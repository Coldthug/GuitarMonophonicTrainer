#include "trainer.h"
#include "ui_trainer.h"

Trainer::Trainer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Trainer)
{

    ui->setupUi(this);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    //获取计时设置的秒数
    timeNum=ui->time_set_spinbox->value();
    //琴品练习范围设置 从几到几 0-26
    form_lattice = ui->formLattice_spinBox->value();
    to_lattice = ui->toLattice_spinBox->value();

    std::cout<<"从"<<form_lattice<<"到"<<to_lattice<<"品"<<std::endl;
    if (form_lattice == 0 && to_lattice == 0) {
        form_lattice = 0;
        to_lattice = 26; // 默认范围
    }

}

Trainer::~Trainer()
{
    delete ui;
}

// 实现TrainerThread类的run方法
void Trainer::TrainerThread::run() {
    while (m_trainer->startOrend) {
        std::cout << "timeNum=" << m_trainer->timeNum << std::endl;
        int i = m_trainer->timeNum - 1;
        for (i = m_trainer->timeNum; i >= 0; i--) {
            std::cout << "i=" << i << std::endl;
            // 使用信号槽机制确保在主线程中更新界面元素，保证线程安全
            QMetaObject::invokeMethod(m_trainer->ui->timeNum_lineEdit, "setText", Qt::QueuedConnection,
                                      Q_ARG(QString, QString::fromStdString(std::to_string(i))));
            QThread::msleep(1000);  // 这里设置每次更新间隔1秒，可根据实际需求调整
        }
        // 琴弦数 - 随机生成的练习指令
        m_trainer->string_num = std::rand() % 6 + 1;
        // 琴品数 - 随机生成的练习指令
        m_trainer->lattice_num = m_trainer->form_lattice + std::rand() % (m_trainer->to_lattice - m_trainer->form_lattice + 1);

        // 使用信号槽机制更新界面上的琴弦数和琴品数显示
        QMetaObject::invokeMethod(m_trainer->ui->string_label, "setText", Qt::QueuedConnection,
                                  Q_ARG(QString, QString::number(m_trainer->string_num)));
        QMetaObject::invokeMethod(m_trainer->ui->lattice_label, "setText", Qt::QueuedConnection,
                                  Q_ARG(QString, QString::number(m_trainer->lattice_num)));
        std::cout << m_trainer->string_num << m_trainer->lattice_num << std::endl;
    }
}

void Trainer::on_startTrainBtn_clicked()
{

    startOrend=1;

    startOrend = 1;
    // 创建并启动线程
    m_thread = new TrainerThread(this);
    m_thread->start();

}



void Trainer::on_endTrainBtn_clicked()
{
    startOrend = 0;
    // 如果线程正在运行，等待线程结束
    if (m_thread->isRunning()) {
        m_thread->wait();
    }
    delete m_thread;
    m_thread = nullptr;
}

void Trainer::on_time_set_spinbox_valueChanged(int arg1)
{
    timeNum = ui->time_set_spinbox->value();
}

void Trainer::on_formLattice_spinBox_valueChanged(int arg1)
{
    form_lattice = ui->formLattice_spinBox->value();
}

void Trainer::on_toLattice_spinBox_valueChanged(int arg1)
{
    to_lattice = ui->toLattice_spinBox->value();
}

void Trainer::on_lineEdit_textChanged(const QString &arg1)
{
    ui->timeNum_lineEdit->text()=timeNum;
}
