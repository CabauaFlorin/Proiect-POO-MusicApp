#include "main_window.h"

main_window::main_window(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
    bar = new QProgressBar(this);
    ui.statusbar->addPermanentWidget(bar);
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    
    connect(player, &QMediaPlayer::positionChanged, this, &main_window::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &main_window::on_durationChanged);
    connect(player, &QMediaPlayer::durationChanged, bar, &QProgressBar::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, bar, &QProgressBar::setValue);
    connect(player, &QMediaPlayer::stateChanged, this, &main_window::repeat);
    connect(player, &QMediaPlayer::stateChanged, this, &main_window::aleatory);

    songs_location.setFileName("songs_location.txt");
    songs_location.open(QIODevice::ReadOnly);

    QStringList list;
    QTextStream in(&songs_location);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QFileInfo info = line;
        list << info.baseName();
        model->setStringList(list);
        ui.listWidget->addItem(info.baseName());
    }
    songs_location.close();
}

void main_window::repeat()
{
    if (player->state() == QMediaPlayer::State::StoppedState && ui.repeat_toolbar->isChecked() == true && ui.aleatory_toolbar->isChecked() == false)
    {
        player->setPosition(0);
        player->play();
        /*QListWidgetItem* item = ui.listWidget->currentItem();
     

        songs_location.setFileName("songs_location.txt");
        songs_location.open(QIODevice::ReadOnly);
        QTextStream in(&songs_location);
        int linie = 0;
        while (!in.atEnd())
        {
            QString line = in.readLine();
            linie++;
            if (line.contains(item->text(), Qt::CaseSensitive))
            {
                break;
            }
        }
       
        QString path;
        path = in.readLine();
        QFileInfo info = path;
        ui.song_name->setText(info.baseName());
        player->setMedia(QUrl::fromLocalFile(info.absoluteFilePath()));
        player->play();*/
    }
}

void main_window::aleatory()
{
    if (player->state() == QMediaPlayer::State::StoppedState && ui.aleatory_toolbar->isChecked() == true && ui.repeat_toolbar->isChecked() == false)
    {
        songs_location.setFileName("songs_location.txt");
        songs_location.open(QIODevice::ReadOnly);
        srand(time(0));
        int row = (rand() % (songs_location.size()));
        int linii = 0;
        songs_location.seek(0);
        while (songs_location.atEnd())
        {
            linii++;
            if (linii == row)
            {
                QString line = songs_location.readLine();
                player->setMedia(QUrl::fromLocalFile(line));
                player->play();
            }
        }
    }
}

void main_window::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, "Open File");
    if (path.isEmpty())
        return;

    write_song_location(path);

    songs_location.setFileName("songs_location.txt");
    songs_location.open(QIODevice::ReadOnly);
    int rows = songs_location.size();

    QFileInfo info = path;
    ui.listWidget->insertItem(rows, info.baseName());

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

void main_window::on_listWidget_itemClicked(QListWidgetItem* item)
{
    ui.song_name->setText(item->text());
    songs_location.setFileName("songs_location.txt");
    songs_location.open(QIODevice::ReadOnly);
    QTextStream in(&songs_location);
    QString path;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.contains(item->text(), Qt::CaseSensitive))
        {
            path = line;
        }
    }
    player->setMedia(QUrl::fromLocalFile(path));
    player->play();
}

void main_window::on_next_button_clicked()
{
    QString current_song = ui.song_name->text();
    songs_location.setFileName("songs_location.txt");
    songs_location.open(QIODevice::ReadOnly);
    QTextStream in(&songs_location);
    int row = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.contains(current_song, Qt::CaseSensitive))
        {
            row++;
            break;
        }
        row++;
    }
    songs_location.seek(0);
    row++;
    QString path;
    for (int i = 0; i < songs_location.size(); i++)
    {
        if (row == i)
        {
            path = in.readLine();
        }
    }
    QFileInfo info = path;
    ui.song_name->setText(info.baseName());
    player->setMedia(QUrl::fromLocalFile(path));
    player->play();
}

void main_window::on_previous_button_clicked()
{
    QString current_song = ui.song_name->text();
    songs_location.setFileName("songs_location.txt");
    songs_location.open(QIODevice::ReadOnly);
    QTextStream in(&songs_location);
    int linii = 0, row = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.contains(current_song, Qt::CaseSensitive))
        {
            break;
        }
        linii++;
    }
    in.seek(0);
    QString path;
    for (int i = 0; i < songs_location.size(); i++)
    {
        QString line = in.readLine();
        if ((linii - 1) == i)
        {
            path = line;
        }
        /*else if ((linii - 1) < 0)
        {
            path = in.readLine();
        }*/
    }
    QFileInfo info = path;
    ui.song_name->setText(info.baseName());
    player->setMedia(QUrl::fromLocalFile(path));
    player->play();
}

void main_window::on_next_toolbar_triggered()
{
    QString current_song = ui.song_name->text();
    songs_location.setFileName("songs_location.txt");
    songs_location.open(QIODevice::ReadOnly);
    QTextStream in(&songs_location);
    int row = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.contains(current_song, Qt::CaseSensitive))
        {
            row++;
            break;
        }
        row++;
    }
    songs_location.seek(0);
    row++;
    QString path;
    for (int i = 0; i < songs_location.size(); i++)
    {
        if (row == i)
        {
            path = in.readLine();
        }
    }
    QFileInfo info = path;
    ui.song_name->setText(info.baseName());
    player->setMedia(QUrl::fromLocalFile(path));
    player->play();
}

void main_window::on_previous_toolbar_triggered()
{
    QString current_song = ui.song_name->text();
    songs_location.setFileName("songs_location.txt");
    songs_location.open(QIODevice::ReadOnly);
    QTextStream in(&songs_location);
    int linii = 0, row = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.contains(current_song, Qt::CaseSensitive))
        {
            break;
        }
        linii++;
    }
    in.seek(0);
    QString path;
    for (int i = 0; i < songs_location.size(); i++)
    {
        QString line = in.readLine();
        if ((linii - 1) == i)
        {
            path = line;
        }
        /*else if ((linii - 1) < 0)
        {
            path = in.readLine();
        }*/
    }
    QFileInfo info = path;
    ui.song_name->setText(info.baseName());
    player->setMedia(QUrl::fromLocalFile(path));
    player->play();
}