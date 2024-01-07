#ifndef CSTUINFO_H
#define CSTUINFO_H
#include <QString>
#include <iostream>

class CStuInfo
{
public:
    CStuInfo();
    CStuInfo(int id, QString name, QString sex, QString phone, int cet4, double gpa);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString sex() const;
    void setSex(const QString &sex);

    QString phone() const;
    void setPhone(const QString &phone);

    int cet4() const;
    void setCet4(int cet4);

    double gpa() const;
    void setGpa(double gpa);

    double overallScore() const;
    void setOverallScore(double overallScore);

    friend std::ostream &operator<<(std::ostream &os, const CStuInfo &stuinfo);

private:
    int m_id ; // 学生ID，4位
    QString m_name; // 姓名
    QString m_sex ; // 性别，男/女
    QString m_phone; // 手机号，11位
    int m_cet4 ; // 四级成绩，0-750
    double m_gpa;// 平均成绩，0-4
    double  m_overallScore; // 总成绩，100 = m_cet4 * 0.04 + m_gpa * 17.5
};


#endif // CSTUINFO_H
