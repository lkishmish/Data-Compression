void buildFrequencyMap(string filename, bool isFile, hashmapF &map) {
    string fileline;
	
    if(isFile){// if there is a file 
		
        ifstream infs(filename);
        // while loop to parse file line string 
        while(!infs.eof()){
            //get lines of strings in file 
            getline(infs,fileline);
            // get filelline and separate chars in string 
            // and put into the map
            for(unsigned i = 0; i < fileline.size(); i++){
                if(map.containsKey(fileline[i])){
                    map.put(fileline[i],map.get(fileline[i])+1);
                }
                else{
                    map.put(fileline[i],1);
                }
            }
        }
        map.put( PSEUDO_EOF,1);
    }
    else{//we parse through the string 
        for(unsigned i = 0; i < filename.length(); i++){
            if(map.containsKey(filename[i])){
                map.put(filename[i],map.get(filename[i])+1);
            }
            else{
                map.put(filename[i],1);
            }
        }
        map.put( PSEUDO_EOF,1);
    }    
}


// string abcbacbade
// a b c b a c b a d  e  \n
// 1 2 3 4 5 6 7 8 9 10  11
