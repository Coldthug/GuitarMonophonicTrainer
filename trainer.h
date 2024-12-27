

#ifndef TRAINER_H
#define TRAINER_H

#include <QWidget>
#include <cstdlib>
#include <ctime>
#include<iostream>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class Trainer; }
QT_END_NAMESPACE

class Trainer : public QWidget
{
    Q_OBJECT

public:
    Trainer(QWidget *parent = nullptr);
    ~Trainer();

    void Trainer_thread();


private slots:
    //开始练习
    void on_startTrainBtn_clicked();
    //结束练习
    void on_endTrainBtn_clicked();

    void on_time_set_spinbox_valueChanged(int arg1);

    void on_formLattice_spinBox_valueChanged(int arg1);

    void on_toLattice_spinBox_valueChanged(int arg1);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Trainer *ui;
    int timeNum = 0;
    int form_lattice = 1;
    int to_lattice = 26;
    int string_num = 0;
    int lattice_num = 0;
    bool startOrend = false;

    // 新增线程类成员变量
    class TrainerThread : public QThread {
    public:
        TrainerThread(Trainer *parent) : QThread(parent), m_trainer(parent) {}
    protected:
        void run() override;
    private:
        Trainer *m_trainer;
    };
    TrainerThread *m_thread;





};
#endif // TRAINER_H
