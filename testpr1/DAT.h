#ifndef ENUMEXEC_H
#define ENUMEXEC_H
#include <QString>
#define _ DAT

class DAT {
public:
    static QString LOG,
    BLOK,
    KA,
    BI,
    PARM,
    SOL,
    PARMLOG,
    FILELOG,

    LOGID,
    LOGDATE,
    LOGBLOK,
    LOGSOL,
    LOGSOLDATE,
    LOGDESC,

    BLOKID,
    BLOKSERIAL,
    BLOKNAME,
    BLOKBI,

    KAID,
    KANAME,
    KADATE,
    KADESC,

    BIID,
    BISERIAL,
    BINAME,
    BIKA,

    PARMID,
    PARMNAME,
    PARMDESC,

    SOLID,
    SOLNAME,
    SOLDESC,

    PARMLOGID,
    PARMLOGLOG,
    PARMLOGPARM,
    PARMLOGCOND,
    PARMLOGFILE,

    FILELOGID,
    FILELOGNAME;

public:
        DAT();

};

        enum class Enumerr:int{
            CONNECTIONOK,
            CONNECTIONERROR,
            READINGOK,
            READINGERROR,
            METALOADERROR,
            SAVINGERROR,
            SAVINGOK
        };
#endif // ENUMEXEC_H
