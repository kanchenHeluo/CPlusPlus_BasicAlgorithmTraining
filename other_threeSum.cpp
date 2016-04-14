#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int cmp(const int a, const int b){
	return a<b;
}

vector<vector<int> > twoSum(vector<int> nums, int s, int target){
	vector<int> baknums;
	vector<vector<int> > result;
	int len = nums.size();
	for(int i=s; i<len;i++){
		baknums.push_back(nums[i]);
	}
	int i=0, j=baknums.size()-1;
	while(i < j){
		int sum = baknums[i]+baknums[j];
		if(sum < target){
			i++;
		}else if(sum >target){
			j--;
		}else{
			vector<int> re;
			re.push_back(baknums[i]);
			re.push_back(target-baknums[i]);
			result.push_back(re);
			
			do{
				i ++;	
			}while(i<j && baknums[i] == baknums[i-1]);
			
			do{
				j --;	
			}while(j>i && baknums[j] == baknums[j+1]);
		}	
	}
	
	return result;
}

vector<vector<int> > threeSum(vector<int> nums){
	vector<vector<int> > result;
	map<int, int> m;	
	int len=nums.size();
	
	sort(nums.begin(), nums.end(), cmp);
	for(int i=0; i<len-2 && nums[i] <= 0; i++){
	    if(i>0 && nums[i] == nums[i-1]){
	        continue;
	    }
		vector< vector<int> > result2 = twoSum(nums, i+1, 0 - nums[i]);
		int len2 = result2.size();
		
		for(int k=0; k<len2; k++){
			vector<int> tmp;
			tmp.push_back(nums[i]);
			tmp.push_back(result2[k][0]);
			tmp.push_back(result2[k][1]);
			result.push_back(tmp);	
		}
	}
	
	return result;
}


int main(){
	vector<int> sample(7);
	sample[0] = -7;
	sample[1] = -2;
	sample[2] = -3;
	sample[3] = 0;
	sample[4] = 5;
	sample[5] = 2;
	sample[6] = 9;
	
	vector< vector<int> > result;
	result = threeSum(sample);
	
	int i,j;
	for(i=0; i<result.size(); i++){
		for(j=0; j<result[i].size(); j++){
			cout << result[i][j] << ",";	
		}
		cout << endl;
	}
	
	return 0;
}
