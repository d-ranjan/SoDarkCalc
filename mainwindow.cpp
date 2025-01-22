#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "sodark.h"

#include <QDebug>
#include <QMessageBox>
#include <cassert>

#include <fmt/ranges.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // fmt::println("{::#}", std::views::iota(0,10));

    static_assert(sodark3::encrypt(1, 0x54e0cd, 0xc2284a1ce7be2f, 0x543bd88000017550) == 0xD0721D);
    static_assert(sodark3::decrypt(1, 0xD0721D, 0xc2284a1ce7be2f, 0x543bd88000017550) == 0x54e0cd);
    static_assert(sodark3::encrypt(3, 0x54e0cd, 0xc2284a1ce7be2f, 0x543bd88000017550) == 0x41DB0C);
    static_assert(sodark3::decrypt(3, 0x41DB0C, 0xc2284a1ce7be2f, 0x543bd88000017550) == 0x54e0cd);
    static_assert(sodark3::encrypt(8, 0x54e0cd, 0xc2284a1ce7be2f, 0x543bd88000017550) == 0xC0D705);
    static_assert(sodark3::decrypt(8, 0xC0D705, 0xc2284a1ce7be2f, 0x543bd88000017550) == 0x54e0cd);
    static_assert(sodark6::encrypt(1, 0xdeafcafebabe, 0xc2284a1ce7be2f, 0x543bd88000017550)
                  == 0x963B3C5011FC);
    static_assert(sodark6::decrypt(1, 0x963B3C5011FC, 0xc2284a1ce7be2f, 0x543bd88000017550)
                  == 0xdeafcafebabe);

    connect(ui->pb_calculate, &QPushButton::clicked, [&]() {
        const uint32_t rounds = ui->sb_rounds->value();
        const uint64_t key    = ui->le_key->text().toULongLong(nullptr, 16);
        if (key > 0xFFFFFFFFFFFFFF) {
            QMessageBox::critical(this, "Error", "key is begger than permissible length");
        }
        const uint64_t seed  = ui->le_seed->text().toULongLong(nullptr, 16);
        const uint64_t input = ui->le_input->text().toULongLong(nullptr, 16);
        if (input > 0xFFFFFF) {
            QMessageBox::critical(this, "Error", "input is begger than permissible length");
        }

        if (ui->cb_algorithm->currentIndex() == 0) {
            const auto ct = ui->cb_mode->currentIndex() == 0
                                ? sodark3::encrypt(rounds, static_cast<uint32_t>(input), key, seed)
                                : sodark3::decrypt(rounds, static_cast<uint32_t>(input), key, seed);

            ui->le_output->setText(QString::number(ct, 16).toUpper());
        } else {
            const auto pt = ui->cb_mode->currentIndex() == 0
                                ? sodark6::encrypt(rounds, input, key, seed)
                                : sodark6::decrypt(rounds, input, key, seed);
            ui->le_output->setText(QString::number(pt, 16).toUpper());
        }
    });
}

MainWindow::~MainWindow() { delete ui; }
