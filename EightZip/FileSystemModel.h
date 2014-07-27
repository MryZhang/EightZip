// FileSystemModel.h

#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <memory>

#include "ModelBase.h"

class FileSystemModel
    : public ModelBase
{
    struct Private { };

public:
    FileSystemModel(TString tstrFullPath);
    FileSystemModel(Private) { }

    virtual std::shared_ptr<IModel> GetParent() const;
    virtual const std::vector<ItemType> &GetChildrenSupportedItems() const;

protected:
    virtual void _UpdateChildren();

private:
    static std::vector<ItemType> m_vType;

    static std::shared_ptr<FileSystemModel> __MakeShared();

};

#endif // FILESYSTEMMODEL_H
