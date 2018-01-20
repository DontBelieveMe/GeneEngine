using System;
using System.Collections.Generic;
using System.Text;

namespace ModelConverter.Source
{
    interface IConverter
    {
        GeneModel ToGeneModel();
    }
}
