import os
import re

currentYear = "2018"

header = "// Copyright 2017-" + currentYear + " Barney Wilks. All Rights Reserved"
searchRegex = "\/\/ Copyright 2017-([0-9]{4}) Barney Wilks\. All Rights Reserved"

for root, directories, filenames in os.walk('Gene/Engine'):
    for filename in filenames: 
        path = os.path.join(root, filename)
        filename, file_extension = os.path.splitext(path)

		# We only want to process C++ files
        if file_extension == ".cc" or file_extension == ".h":
            f = open(path, "r")
            txt = f.read()
			
			# If the notice already exists just replace it 
            if re.match(searchRegex, txt):
                txt = re.sub(searchRegex, header, txt)
            else:
                txt = header + '\n' + txt
            
            f.close()
            f = open(path, "w")
            f.write(txt)
            f.close()
