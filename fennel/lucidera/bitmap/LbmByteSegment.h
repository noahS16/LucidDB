/*
// $Id$
// Fennel is a library of data storage and processing components.
// Copyright (C) 2005-2005 LucidEra, Inc.
// Copyright (C) 2005-2005 The Eigenbase Project
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version approved by The Eigenbase Project.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef Fennel_LbmByteSegment_Included
#define Fennel_LbmByteSegment_Included

#include "fennel/common/CommonPreamble.h"
#include "fennel/common/ByteBuffer.h"
#include "fennel/lucidera/bitmap/LbmSegment.h"

FENNEL_BEGIN_NAMESPACE

/**
 * This class encapsulates a single byte segment, as opposed to
 * a tuple which contains a set of them
 */    
class LbmByteSegment
{
public:
    LbmByteNumber byteNum;
    PBuffer byteSeg;
    uint len;

    inline void reset() 
    {
        byteNum = (LbmByteNumber) 0;
        byteSeg = NULL;
        len = 0;
    }

    /**
     * Returns the Srid of the starting byte (not the first rid set)
     */
    inline LcsRid getSrid() const
    {
        return byteNumberToRid(byteNum);
    }

    /**
     * Whether the segment has valid data
     */
    inline bool isNull() const
    {
        return byteSeg == NULL;
    }

    /**
     * Returns the end byte number
     */
    inline LbmByteNumber getEnd() const
    {
        return byteNum + len;
    }

    /**
     * Returns the end rid (one past last valid rid)
     */
    inline LcsRid getEndRid() const
    {
        return byteNumberToRid(getEnd());
    }

    /**
     * Ensures the segment begins with the requested byte number.
     * As a result, the beginning of the segment or even the entire
     * segment may be truncated.
     *
     * This function assumes bytes are reverse order.
     */
    void advanceToByteNum(LbmByteNumber newStartByteNum) 
    {
        // ignore null values
        if (isNull()) {
            return;
        }
        
        // check if the segment will have valid data after truncation
        if (getEnd() <= newStartByteNum) {
            reset();
            return;
        }

        // advance the segment in place if required
        if (byteNum < newStartByteNum) {
            uint diff = opaqueToInt(newStartByteNum - byteNum);
            byteNum += diff;
            byteSeg -= diff;
            len -= diff;
        }
    }

    /**
     * Prints a byte segment.
     *
     * This function assumes bytes are in order.
     */
    void print(std::ostream &output) 
    {
        output << std::dec << opaqueToInt(byteNum) << ".";
        output << std::dec << len << " (";
        for (uint i = 0; i < len; i++) {
            uint val = byteSeg[i];
            if (i > 0) {
                output << ",";
            }
            output << std::hex << val;
        }
        output << ")" << std::endl;
    }
};

FENNEL_END_NAMESPACE

#endif

// End LbmByteSegment.h