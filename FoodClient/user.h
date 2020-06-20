#ifndef USER_H
#define USER_H

#include <QString>
#include <QDataStream>

class User {
public:
    User();
    friend QDataStream &operator>>(QDataStream &s, User &user);
    friend QDataStream &operator<<(QDataStream &s, const User &user);
private:
    int uid, utype;
    QString uname, password, photo;
public:
    QString getUserInfo();
    int getUid() const;

    void setUid(int uid);

    int getUtype() const;

    void setUtype(int utype);

    const QString &getUname() const;

    void setUname(const QString &uname);

    const QString &getPassword() const;

    void setPassword(const QString &password);

    const QString &getPhoto() const;

    void setPhoto(const QString &photo);


};

#endif // USER_H
