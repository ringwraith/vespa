// Copyright 2017 Yahoo Holdings. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

#pragma once

#include "iattributesavetarget.h"
#include "attributefilewriter.h"

namespace search
{

/**
 * Class used to save an attribute vector to file(s).
 **/
class AttributeFileSaveTarget : public IAttributeSaveTarget
{
private:
    AttributeFileWriter _datWriter;
    AttributeFileWriter _idxWriter;
    AttributeFileWriter _weightWriter;
    AttributeFileWriter _udatWriter;

public:
    AttributeFileSaveTarget(const TuneFileAttributes &tuneFileAttributes,
                            const search::common::FileHeaderContext &
                            fileHeaderContext);
    ~AttributeFileSaveTarget();

    // Implements IAttributeSaveTarget
    /** Setups this saveTarget by opening the relevant files **/
    virtual bool setup() override;

    /** Closes the files used **/
    virtual void close() override;

    virtual IAttributeFileWriter &datWriter() override;
    virtual IAttributeFileWriter &idxWriter() override;
    virtual IAttributeFileWriter &weightWriter() override;
    virtual IAttributeFileWriter &udatWriter() override;
};

} // namespace search

