#include "gitcommitobj.h"

GitCommitObj::GitCommitObj()
{

}

GitCommitObj::~GitCommitObj() {
    commit_list_parentID.clear();
}


QString GitCommitObj::convertIdString(git_oid id)
{
    QString str;
    unsigned char *pid = (unsigned char *) &id;

    for(int i=0 ; i < sizeof(git_oid) ; i++) {
        unsigned char tmp = pid[i];
        str.append(QString::number(tmp, 16).rightJustified(2, '0'));
    }

    return str;
}
