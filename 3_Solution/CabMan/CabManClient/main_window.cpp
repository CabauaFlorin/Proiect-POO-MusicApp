#include "main_window.h"

main_window::main_window(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
    ui.statusbar->addPermanentWidget(bar);
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    connect(player, &QMediaPlayer::positionChanged, this, &main_window::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &main_window::on_durationChanged);
    connect(player, &QMediaPlayer::durationChanged, bar, &QProgressBar::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, bar, &QProgressBar::setValue);
    connect(model, SIGNAL(clicked), this, SLOT(LineClicked(QModelIndex)));

    songs_location.setFileName("songs_location.txt");
    songs_location.open(QIODevice::ReadOnly);

    //QStringListModel* model = new QStringListModel(this);
    QStringList list;
    QTextStream in(&songs_location);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QFileInfo info = line;
        list << info.baseName();
        model->setStringList(list);
        ui.listView->setModel(model);
    }
    songs_location.close();
}

int pozitia = 0;

void main_window::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, "Open File");
    if (path.isEmpty())
        return;

    write_song_location(path);

    /*QMediaContent song1(path);
    if (playlist->isEmpty())
    {
        pozitia = 2;
        playlist->addMedia(song1);
        QString fn = QFileDialog::getSaveFileName(this, "Save file", QDir::currentPath(), "Text files (.txt);;All files (.*)");
        qDebug() << playlist->save(QUrl::fromLocalFile(fn), "m3u");
    }
    else
    {
        playlist->insertMedia(pozitia, song1);
        pozitia++;
    }*/

   /* QFile file(path);
    
    QStringListModel* model = new QStringListModel(this);
    QStringList list;

    QFileInfo info = path;
    list << info.baseName();
    ui.song_name->setText(info.baseName());

    model->setStringList(list);
    ui.listView->setModel(model);
    player->setMedia(QUrl::fromLocalFile(path));*/
}

void main_window::write_song_location(QString path)
{
    songs_location.setFileName("songs_location.txt");
    songs_location.open(QIODevice::ReadOnly);
    QTextStream in(&songs_location);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.toStdString() == path.toStdString())
        {
            songs_location.close();
            return;
        }
    }
    songs_location.close();
    songs_location.open(QIODevice::Append);
    QTextStream stream(&songs_location);
    stream << path << "\n";
    songs_location.close();
}

void main_window::LineClicked(QModelIndex index)
{
    QString sir = index.data().toString();
    ui.song_name->setText(sir);
    player->setMedia(QUrl::fromLocalFile(sir));
}

void main_window::on_add_file_button_triggered()
{
    openFile();
}

void main_window::on_play_button_clicked()
{
    player->play();
    qDebug() << player->errorString();
}

void main_window::on_play_toolbar_triggered()
{
    player->play();
    qDebug() << player->errorString();
}

void main_window::on_pause_button_clicked()
{
    player->pause();
}

void main_window::on_pause_toolbar_triggered()
{
    player->pause();
}

void main_window::on_mute_button_clicked()
{
    if (muted==false)
    {
        muted = true;
        player->setMuted(muted);
    }
    else if (muted == true)
    {
        muted = false;
        player->setMuted(muted);
    }
}

void main_window::on_volume_slider_sliderMoved(int position)
{
    player->setVolume(position);
}

void main_window::on_progress_slider_sliderMoved(int position)
{
    player->setPosition(position);
}

void main_window::on_positionChanged(qint64 position)
{
    ui.progress_slider->setValue(position);
}

void main_window::on_durationChanged(qint64 position)
{
    ui.progress_slider->setMaximum(position);
}

void main_window::on_exit_toolbar_triggered()
{
	QApplication::quit();
}