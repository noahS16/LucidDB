/*
// $Id$
// Package org.eigenbase is a class library of data management components.
// Copyright (C) 2005-2005 The Eigenbase Project
// Copyright (C) 2002-2005 Disruptive Tech
// Copyright (C) 2005-2005 LucidEra, Inc.
// Portions Copyright (C) 2003-2005 John V. Sichi
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

package org.eigenbase.util.property;

import java.util.Properties;


/**
 * Definition and accessor for a double-precision property.
 *
 * @author jhyde
 * @since July 5, 2005
 * @version $Id$
 **/
public class DoubleProperty extends Property
{
    //~ Constructors ----------------------------------------------------------

    /**
     * Creates a Double property.
     *
     * @param properties Properties object which holds values for this
     *    property.
     * @param path Name by which this property is serialized to a properties
     *    file, for example "com.acme.trace.Verbosity".
     * @param defaultValue Default value.
     */
    public DoubleProperty(
        Properties properties,
        String path,
        double defaultValue)
    {
        super(properties, path, Double.toString(defaultValue));
    }

    /**
     * Creates a Double property which has no default value.
     *
     * @param properties Properties object which holds values for this
     *    property.
     * @param path Name by which this property is serialized to a properties
     *    file, for example "com.acme.trace.Verbosity".
     */
    public DoubleProperty(
        Properties properties,
        String path)
    {
        super(properties, path, null);
    }

    //~ Methods ---------------------------------------------------------------

    /**
     * Retrieves the value of this double property.
     * If the property has no value, returns the default value.
     * If there is no default value, returns 0.0.
     */
    public double get()
    {
        final String value = getInternal(null, false);
        if (value == null) {
            return 0;
        }
        return Double.parseDouble(value);
    }

    /**
     * Retrieves the value of this double property.
     * If the property has no value, returns the default value.
     * If there is no default value, returns the given default value.
     */
    public double get(int defaultValue)
    {
        final String value = getInternal(null, false);
        if (value == null) {
            return defaultValue;
        }
        return Double.parseDouble(value);
    }
}


// End DoubleProperty.java