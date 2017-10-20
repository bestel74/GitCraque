#ifndef GITCOMMITOBJ_H
#define GITCOMMITOBJ_H

#include <QObject>
#include "git2.h"


class GitCommitObj
{
public:
    GitCommitObj();
    ~GitCommitObj();

    static QString convertIdString(git_oid id);

public:
    git_oid         commit_id;
    QList <git_oid> commit_list_parentID;
    QString         commit_message;
    git_signature   commit_signature;
};

#endif // GITCOMMITOBJ_H
