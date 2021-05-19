#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_main_window.h"
#include <qstringlistmodel.h>
#include <qmediaplayer.h>
#include <qmediaplaylist.h>
#include <qdebug.h>
#include <qprogressbar.h>
#include <qmediacontent.h>

class main_window : public QMainWindow
{
	Q_OBJECT

public:
	main_window(QWidget *parent = Q_NULLPTR);
	~main_window() {}

private:
	Ui::MainWindow ui;
	QMediaPlayer* player;
	QMediaPlaylist* playlist;
	QProgressBar* bar;
	QStringListModel* model = new QStringListModel(this);
	QFile songs_location;

	bool muted = false;
	void openFile();
	void write_song_location(QString path);

private slots:
	void on_volume_slider_sliderMoved(int position);
	void on_progress_slider_sliderMoved(int position);
	void on_play_button_clicked();
	void on_play_toolbar_triggered();
	void on_pause_button_clicked();
	void on_pause_toolbar_triggered();
	void on_mute_button_clicked();
	void on_positionChanged(qint64 position);
	void on_durationChanged(qint64 position);
	void on_add_file_button_triggered();
	void on_exit_toolbar_triggered();
	void on_listWidget_itemClicked(QListWidgetItem* item);
	void on_next_button_clicked();
	void on_previous_button_clicked();
	void on_next_toolbar_triggered();
	void on_previous_toolbar_triggered();
	void repeat();
	void aleatory();
	
};