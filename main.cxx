#include <QtCore>
#include <QtCoreDepends>
#include <functional>
int main(int argc, char *argv[]) {
    QString outPut = "outFile";
    if (argc == 4) outPut = argv[3]; else if (argc != 3) return argc+100;
    enum { camelCase, PascalCase, snake_case, SCREAMING_SNAKE_CASE };
    struct ProcessArgs {
            QFile file;
            QString arg;
            int type(QString str) {
                QRegularExpression r("[A-Z]");
                bool a = str.at(0).isUpper(),
                        b = str.contains(QChar('_'));
                if (a)
                    if(b) return SCREAMING_SNAKE_CASE;
                    else return PascalCase;
                else if(b) return snake_case;
                else return camelCase;
            }
            std::function<void(int,QString&)> convert;
    } processArgs;
    ; process_args: {
        processArgs.arg = argv[1];
        processArgs.file.setFileName(argv[2]);
        if (!processArgs.file.exists()) return -1;
        processArgs.file.open(QIODevice::ReadOnly | QIODevice::Text);
        processArgs.arg.remove(QChar('['))
                .remove(QChar(']'));
        switch (processArgs.type(processArgs.arg)) {
        case camelCase:
            processArgs.convert = [](int type, QString &str) {
                QStringList list;
                switch (type) {
                case SCREAMING_SNAKE_CASE:
                    str = str.toLower();
                case snake_case:
                    list = str.split(QRegularExpression("_"));
                    for (QString& s : list)
                        s.replace(0, 1, s.at(0).toUpper());
                    str = list.join("");
                case PascalCase:
                    str.replace(0, 1, str.at(0).toLower());
                }
            };
            break;
        case PascalCase:
            processArgs.convert = [](int type, QString &str) {
                QStringList list;
                switch (type) {
                case SCREAMING_SNAKE_CASE:
                    str = str.toLower();
                case snake_case:
                    list = str.split(QRegularExpression("_"));
                    for (QString& s : list)
                        s.replace(0, 1, s.at(0).toUpper());
                    str = list.join("");
                case camelCase:
                    str.replace(0, 1, str.at(0).toUpper());
                }
            };
            break;
        case snake_case:
            processArgs.convert = [](int type, QString &str) {
                switch (type) {
                case PascalCase:
                    str.replace(0, 1, str.at(0).toLower());
                case camelCase:
                    str = str.split(QRegularExpression("(?=[A-Z])"))
                          .join(QChar('_'));
                case SCREAMING_SNAKE_CASE:
                    str = str.toLower();
                }
            };
            break;
        case SCREAMING_SNAKE_CASE:
            processArgs.convert = [](int type, QString &str) {
                switch (type) {
                case PascalCase:
                    str.replace(0, 1, str.at(0).toLower());
                case camelCase:
                    str = str.split(QRegularExpression("(?=[A-Z])"))
                          .join(QChar('_'));
                case snake_case:
                    str = str.toUpper();
                }
            };
        }
    }
    struct ProcessFile {
            int type;
            QStringList line;
            QTextStream dest, source;
            ProcessFile(QIODevice * d, QString f, int t) {
                type = t; out = new QFile(f);
                out->open(QIODevice::WriteOnly | QIODevice::Text);
                this->source.setDevice(d);
                this->dest.setDevice(out);
            }
            ~ProcessFile() { delete out; }
        private:
            QFile * out;
    } processFile(&processArgs.file, outPut, processArgs.type(processArgs.arg));
    ; process_file: {
        if (processFile.source.atEnd()) {
            processFile.dest.flush();
            processFile.dest.device()->close();
            processFile.source.device()->close();
        } else {
            processFile.line = processFile.source
                               .readLine()
                               .simplified()
                               .split(QChar(' '), QString::SkipEmptyParts);
            for ( QString& s : processFile.line )
                processArgs.convert(processArgs.type(s), s);
            processFile.dest << processFile.line.join(QChar(' ')) << endl;
            goto process_file;
        }
    } return 0;
}
