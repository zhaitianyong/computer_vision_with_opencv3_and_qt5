#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PLUGINS_SUBFOLDER                   "/plugins/"
#define LANGUAGES_SUBFOLDER                 "/languages/"
#define THEMES_SUBFOLDER                    "/themes/"
#define FILE_ON_DISK_DYNAMIC_PROPERTY       "absolute_file_path"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSettings(); // First thing's first, load settings

    // load all plugin dlls
    populatePluginsMenu();

    //
    populateLanguagesMenu();
    populateThemesMenu();

    ui->graphicsView->setScene(&scene);
    scene.addItem(&originalPixmap);
    scene.addItem(&processedPixmap);

    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

MainWindow::~MainWindow()
{
    delete currentPlugin;
    delete ui;
}

void MainWindow::loadSettings()
{
    QSettings settings("Packt", "Computer_Vision", this);
    currentThemeFile = settings.value("currentThemeFile", "").toString();
    currentLanguageFile = settings.value("currentLanguageFile", "").toString();
    currentPluginFile = settings.value("currentPluginFile", "").toString();
}

void MainWindow::saveSettings()
{
    QSettings settings("Packt", "Computer_Vision", this);
    settings.setValue("currentThemeFile", currentThemeFile);
    settings.setValue("currentLanguageFile", currentLanguageFile);
    settings.setValue("currentPluginFile", currentPluginFile);
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
    else
    {
        QMainWindow::changeEvent(event);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::warning(this, tr("Exit"), tr("Are you sure you want to exit?"), QMessageBox::Yes, QMessageBox::No);
    if(result == QMessageBox::Yes)
    {
        saveSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

/**
 * 遍历Plugins文件下的所有Dll插件
 */
void MainWindow::populatePluginsMenu()
{
    // Load all plugins and populate the menus
    QDir pluginsDir(qApp->applicationDirPath() + PLUGINS_SUBFOLDER);
    QFileInfoList pluginFiles = pluginsDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    foreach(QFileInfo pluginFile, pluginFiles)
    {
        if(pluginFile.suffix().compare("dll")!=0) continue; // 只搜索dll后缀的文件
        if(QLibrary::isLibrary(pluginFile.absoluteFilePath()))
        {
            // 初始化插件，并创建菜单项
            QPluginLoader pluginLoader(pluginFile.absoluteFilePath(), this);
            if(CvPluginInterface *plugin = dynamic_cast<CvPluginInterface*>(pluginLoader.instance()))
            {
                QAction *pluginAction = ui->menu_Plugins->addAction(plugin->title());
                pluginAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, pluginFile.absoluteFilePath());
                connect(pluginAction, SIGNAL(triggered(bool)), this, SLOT(onPluginActionTriggered(bool)));

                // 设置当前插件的路径
                if(currentPluginFile == pluginFile.absoluteFilePath())
                {
                    pluginAction->trigger();
                }
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"),
                                     QString(tr("Make sure %1 is a correct plugin for this application<br>"
                                                "and it's not in use by some other application!")).arg(pluginFile.fileName()));
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Warning"),
                                 QString(tr("Make sure only plugins exist in %1 folder.<br>"
                                            "%2 is not a plugin."))
                                 .arg(PLUGINS_SUBFOLDER)
                                 .arg(pluginFile.fileName()));
        }
    }

    if(ui->menu_Plugins->actions().count() <= 0)
    {
        QMessageBox::critical(this, tr("No Plugins"), QString(tr("This application cannot work without plugins!"
                                                                 "<br>Make sure that %1 folder exists "
                                                                 "in the same folder as the application<br>and that "
                                                                 "there are some filter plugins inside it")).arg(PLUGINS_SUBFOLDER));
        this->setEnabled(false);
    }
}

void MainWindow::populateLanguagesMenu()
{
    QMenu *languagesMenu = new QMenu(this);
    // Add default (english) language
    QAction *defaultLanguageAction = languagesMenu->addAction("English - US");
    defaultLanguageAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, "");
    connect(defaultLanguageAction, SIGNAL(triggered(bool)), this, SLOT(onLanguageActionTriggered(bool)));

    // Load all languages and populate the menus
    QDir languagesDir(qApp->applicationDirPath() + LANGUAGES_SUBFOLDER);
    QFileInfoList languageFiles = languagesDir.entryInfoList(QStringList() << "*.qm", QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    foreach(QFileInfo languageFile, languageFiles)
    {
        QAction *languageAction = languagesMenu->addAction(languageFile.baseName());
        languageAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, languageFile.absoluteFilePath());
        connect(languageAction, SIGNAL(triggered(bool)), this, SLOT(onLanguageActionTriggered(bool)));

        if(currentLanguageFile == languageFile.absoluteFilePath())
        {
            languageAction->trigger();
        }
    }
    ui->actionLanguage->setMenu(languagesMenu);
}

void MainWindow::populateThemesMenu()
{
    QMenu *themesMenu = new QMenu(this);
    // Add default (native) theme
    QAction *defaultThemeAction = themesMenu->addAction("Default");
    defaultThemeAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, "");
    connect(defaultThemeAction, SIGNAL(triggered(bool)), this, SLOT(onThemeActionTriggered(bool)));

    // Load all themes and populate the menus
    QDir themesDir(qApp->applicationDirPath() + THEMES_SUBFOLDER);
    QFileInfoList themeFiles = themesDir.entryInfoList(QStringList() << "*.thm", QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    foreach(QFileInfo themeFile, themeFiles)
    {
        QAction *themeAction = themesMenu->addAction(themeFile.baseName());
        themeAction->setProperty(FILE_ON_DISK_DYNAMIC_PROPERTY, themeFile.absoluteFilePath());
        connect(themeAction, SIGNAL(triggered(bool)), this, SLOT(onThemeActionTriggered(bool)));

        if(currentThemeFile == themeFile.absoluteFilePath())
        {
            themeAction->trigger();
        }
    }
    ui->actionTheme->setMenu(themesMenu);
}

void MainWindow::on_actionAboutQt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

/**
 * 点击菜单，显示当前插件界面
 */
void MainWindow::onPluginActionTriggered(bool)
{
    if(!currentPlugin.isNull())
    {
        delete currentPlugin;
        delete currentPluginGui;
    }

    // 实例化当前插件
    currentPluginFile = QObject::sender()->property(FILE_ON_DISK_DYNAMIC_PROPERTY).toString();
    currentPlugin = new QPluginLoader(currentPluginFile, this);
    currentPluginGui = new QWidget(this);
    ui->pluginLayout->addWidget(currentPluginGui);
    CvPluginInterface *currentPluginInstance = dynamic_cast<CvPluginInterface*>(currentPlugin->instance());

    //实例化成功后，初始化界面和连接机制
    if(currentPluginInstance)
    {
        //显示插件的GUI
        currentPluginInstance->setupUi(currentPluginGui);
        //建立主程序和插件的连接机制
        connect(currentPlugin->instance(), SIGNAL(updateNeeded()), this, SLOT(onCurrentPluginUpdateNeeded()));
        connect(currentPlugin->instance(), SIGNAL(infoMessage(QString)), this, SLOT(onCurrentPluginInfoMessage(QString)));
        connect(currentPlugin->instance(), SIGNAL(errorMessage(QString)), this, SLOT(onCurrentPluginErrorMessage(QString)));

    }
}

void MainWindow::onLanguageActionTriggered(bool)
{
    currentLanguageFile = QObject::sender()->property(FILE_ON_DISK_DYNAMIC_PROPERTY).toString();
    qApp->removeTranslator(&translator);
    if(!currentLanguageFile.isEmpty())
    {
        translator.load(currentLanguageFile);
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }
}

void MainWindow::onThemeActionTriggered(bool)
{
    currentThemeFile = QObject::sender()->property(FILE_ON_DISK_DYNAMIC_PROPERTY).toString();
    QFile themeFile(currentThemeFile);
    if(currentThemeFile.isEmpty())
    {
        qApp->setStyleSheet("");
    }
    else
    {
        themeFile.open(QFile::ReadOnly | QFile::Text);
        QString styleSheet = themeFile.readAll();
        qApp->setStyleSheet(styleSheet);
        themeFile.close();
    }
}

void MainWindow::on_actionOpenImage_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Input Image"),
                                                    QDir::currentPath(),
                                                    tr("Images") + " (*.jpg *.png *.bmp)");


    if(fileName.trimmed().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Make sure the image file exists "
                                 "and it is accessible!"));
    }else{
        originalMat = cv::imread(fileName.toStdString());
        originalImage =  QOpenCV::wrapImage(originalMat);
        //originalImage = QImage(originalMat.data, originalMat.cols, originalMat.rows, originalMat.step, QImage::Format_RGB888);
        originalPixmap.setPixmap(QPixmap::fromImage(originalImage));
    }

}

void MainWindow::on_viewOriginalCheck_toggled(bool checked)
{
    originalPixmap.setVisible(checked);
    processedPixmap.setVisible(!checked);
}

/**
 * 插件的调用，当接收到插件对象updateNeeded信号，就触发主窗口调用processImage
 */
void MainWindow::onCurrentPluginUpdateNeeded()
{
    if(!originalMat.empty())
    {
        if(!currentPlugin.isNull())
        {
            CvPluginInterface *currentPluginInstance = dynamic_cast<CvPluginInterface*>(currentPlugin->instance());
            if(currentPluginInstance)
            {
                cv::TickMeter meter;
                meter.start();
                currentPluginInstance->processImage(originalMat, processedMat);
                meter.stop();
                qDebug() << "The process took " << meter.getTimeMilli() << "milliseconds";
            }
        }
        else
        {
            processedMat = originalMat.clone();
        }

        originalImage =  QOpenCV::wrapImage(originalMat);
        //QImage(originalMat.data, originalMat.cols, originalMat.rows, originalMat.step, QImage::Format_RGB888);
        originalPixmap.setPixmap(QPixmap::fromImage(originalImage));

        processedImage =  QOpenCV::wrapImage(processedMat);
        //processedImage = QImage(processedMat.data, processedMat.cols, processedMat.rows, processedMat.step, QImage::Format_RGB888);
        processedPixmap.setPixmap(QPixmap::fromImage(processedImage));
    }
}

void MainWindow::on_actionSaveImage_triggered()
{
    if(!ui->viewOriginalCheck->isChecked() && !processedMat.empty())
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::currentPath(), "*.jpg;;*.png;;*.bmp");
        if(!fileName.isEmpty())
        {
            cv::imwrite(fileName.toStdString(), processedMat);
        }
    }
    else if(ui->viewOriginalCheck->isChecked() && !originalMat.empty())
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::currentPath(), "*.jpg;;*.png;;*.bmp");
        if(!fileName.isEmpty())
        {
            cv::imwrite(fileName.toStdString(), originalMat);
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"), tr("There is nothing to be saved!"));
    }
}

void MainWindow::onCurrentPluginErrorMessage(QString msg)
{
    qDebug() << "Plugin Error Message : " << msg;
}

void MainWindow::onCurrentPluginInfoMessage(QString msg)
{
    qDebug() << "Plugin Info Message : " << msg;
}

void MainWindow::on_action_Camera_triggered()
{

}
