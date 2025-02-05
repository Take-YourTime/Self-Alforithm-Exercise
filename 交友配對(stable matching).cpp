#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
using namespace std;


//	the girl rank by each boy
map<string, vector<string> > boyLike = {
    {"Michael", {"Sophia",	"Sarah",	"Jessica",	"Emily",	"Linda"}	},
    {"John",    {"Jessica",	"Emily",	"Sophia",	"Linda",	"Sarah"}	},
    {"David",   {"Sophia",	"Sarah",	"Linda",	"Emily",	"Jessica"}	},
    {"James",   {"Sophia",	"Emily",	"Jessica",	"Sarah",	"Linda"}	},
    {"Robert",  {"Jessica",	"Linda",	"Sophia",	"Emily",	"Sarah",}	}
};

//	the boy rank by each girl
map<string, map<string, int> > girlLike = {
    {"Sophia",	{{"John", 1},	{"David", 2}, 	{"Michael", 3},	{"James", 4},	{"Robert", 5}}	},
    {"Sarah",	{{"Michael", 1},{"James", 2},	{"David", 3},	{"Robert", 4},	{"John", 5}}	},
    {"Jessica",	{{"Michael", 1},{"David", 2},	{"Robert", 3}, 	{"John", 4},	{"James", 5}}	},
    {"Emily",	{{"James", 1},	{"Michael", 2}, {"Robert", 3},	{"John", 4},	{"David", 5}}	},
    {"Linda",	{{"Michael", 1},{"David", 2}, 	{"James", 3},	{"Robert", 4},	{"John", 5}}	}
};

int main()
{
	/*
	所有男生排隊
	
	由第一位男生開始，依序跟自己最喜歡的女生告白
	
	被告白的女生如果當前沒有對象，女生會答應他，兩人暫時配對成功
	
	但如果被告白的女生當前已有對象了，女生便會將告白者與當前的對象進行比較，並選擇自己較喜歡的人，從而甩掉或拒絕另外一人
	
	重複上述步驟，直到所有人都配對成功，完成 stable matching
	*/
	
	//	紀錄當前配對狀況
	map<string, string> match = {
		{"Sophia",	"====="},
	    {"Sarah",	"====="},
	    {"Jessica",	"====="},
	    {"Emily",	"====="},
	    {"Linda",	"====="}
	};
	
	//	all boys stand in line
	vector<string> boyList = {"Michael", "John", "David", "James", "Robert"};
	
	string boy;		//	a boy
	string choose;	//	the girl choosed by the boy
	while(boyList.size() > 0)
	{
		boy = boyList[0];
		boyList.erase( boyList.begin() );
		
		// boy choose a girl
		choose = boyLike[boy][0];
		boyLike[boy].erase( boyLike[boy].begin() );	//	delete the girl in the boyLike list, since she is choosed
		
		cout << boy << " chooses " << choose << '\n';
		
		//	the girl isn't matched -> match the boy and the girl 
		if(match[choose] == "=====")
		{
			match[choose] = boy;
			cout << choose << " agrees " << boy << '\n';
		}
		//	the girl is matched, and the like the boy more than the matched boy -> change matched person
		else if(girlLike[choose][boy] < girlLike[choose][ match[choose] ])
		{
			//	the last matched boy need to find another girl -> push back to list
			cout << choose << " dumps " << match[choose] << ", then she agrees " << boy << '\n';
			boyList.push_back(match[choose]);
			match[choose] = boy;
		}
		//	the girl is matched, and the like the matched boy more than the boy -> reject the boy
		else
		{
			cout << choose << " rejects " << boy << " since she loves " << match[choose] << " more\n";
			boyList.push_back(boy);
		}
		
		//	output temp matching situation
		cout << "\n\t[ match ]\n";
		for(auto it = match.begin(); it != match.end(); it++)
		{
			cout << '\t' << std::left << setw(10) << it->first << it->second << '\n';
		}
		cout << '\n';
	}
	
	//	final output
	cout << "\n[ Final Matched List ]\n";
	cout << std::left << setw(9) << "boys" << " " << "girls" << '\n';
	cout << std::left << setw(9) << "----" << " " << "-----" << '\n';
	for(auto it = match.begin(); it != match.end(); it++)
	{
		cout << std::left << setw(9) << it->second << " " << it->first << '\n';
	}
	
	return 0;
}
