//string related algorithms



// O(string.length)
//string hashing  [polynomial rolling hash function] --base for rabin karp  
//NOTE : return value must be long long as prime + previous hash value may cross int limit
long long prhf(string s){
   long long hash=0; //as summation
   const int prime = 31; //for A-Z and a-z use prime = 53
   int m = 1e9+7;     //can also use 1e9+9
   long long prime_power=1;  //0th power is 1;

   for(int i=0;i<s.length();i++){
	   hash = hash + (  (s[i]-'a' + 1) *prime_power  ) % m;  /*as cant use 0 for avoiding hash collision*/
	   prime_power = (prime_power * prime) % m;
   }
   return hash;
}



//rabin karp for O(s+t)
vector<int> rabin_karp(string const& s, string const& t) {
    const int p = 31; 
    const int m = 1e9 + 9;
    int S = s.size(), T = t.size();

    vector<long long> p_pow(max(S, T)); 
    p_pow[0] = 1; 
    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(T + 1, 0); 
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
    long long h_s = 0; 
    for (int i = 0; i < S; i++) 
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 

    vector<int> occurences;
    for (int i = 0; i + S - 1 < T; i++) { 
        long long cur_h = (h[i+S] + m - h[i]) % m; 
        if (cur_h == h_s * p_pow[i] % m)
            occurences.push_back(i);
    }
    return occurences;
}


//prefix function   -- base for KMP [Knuth -Morris-Pratt]
vector<int> prefixArray(string s){
	vector<int > prefix (s.length(),0);  // prefix[0] sets pointer for start==0
    
	for(int i=1;i<s.length();i++){
		int j = prefix[i-1];  //previous match of the prefix

		while(j>0 && s[j]!=s[i]){ //prefix mismatch
			j=prefix[j-1];
		}
		if(s[j]==s[i]) j++;

		prefix[i]=j;    //assingning values
	}
	return prefix;
}


//KMP
vector<int> KMP(string text,string patt){
	vector<int> occ;
	vector<int> prefix = prefixArray(patt);
    
	// cout<<"prefix: ";
	// for(auto i :prefix) cout<<i<<" ";
	// cout<<"\n";		
	int i=0,j=0;
	while(i<text.length()){
		if(text[i]==patt[j]){
			j++;i++;
		}
		if(patt.length()==j)  {
			occ.push_back(i-j +1);
			j = prefix[j - 1];   //jump backword after finding string
		}
		else if(i<text.length() && patt[j]!=text[i]){
			if(j!=0) j=prefix[j-1];  //jump backward
			else i+=1;  //skip current and try next letter
		}
		
	}
	return occ;
}


//Z function
vector<int> zfunction(string s){
   vector<int > z(s.length());

   for(int i=1,l=0,r=0;i<s.length();i++){
	   if(i <= r) z[i]=min(r-i+1,z[i-l/*no the l not 1*/]);    //inside the right bound => find the min partition

	   while(i+ z[i]< s.length() && s[z[i]]==s[z[i]+i]){   //trivial method for incrementing the z value
          z[i]++;
	   }

	   if(i+z[i]-1 > r) l=i,r=i+z[i]-1;
   }
   return z;
}
