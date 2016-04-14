#include <iostream>
#include <string.h>
#include <stdexcept> 
using namespace std;

template<typename T>
class heap{
private:
	T* m_h = NULL;
	size_t m_size = 0;
	size_t m_buffersize = 0;
	size_t m_blocklen = 256;
	
	void adjustBottomToTop(int idx){
		int sidx = idx%2==0 ? idx/2-1 : idx/2;
		int tmp = m_h[idx];
		while(sidx >= 0){
			if(tmp < m_h[sidx]){
				break;
			}
			m_h[idx] = m_h[sidx];
			idx = sidx;
			sidx = sidx%2==0? sidx/2-1 : sidx/2;
		}
		//cout << idx;
		m_h[idx] = tmp;
	}
	
	void adjustTopToBottom(int idx){
		int leftidx = idx*2+1, rightidx = 2*idx+2;
		int tmp = m_h[idx];
		
		while(leftidx < m_size){
			int max_val = m_h[leftidx], max_idx = leftidx;
			if(rightidx < m_size && m_h[rightidx] > max_val){
				max_val = m_h[rightidx];
				max_idx = rightidx;
			}
			
			if(max_val < tmp){
				break;
			}
			
			m_h[idx] = max_val;
			idx = max_idx;
			leftidx = idx*2+1;
			rightidx = 2*idx+2;			
		}
		
		m_h[idx] = tmp;
	}
	
public:
	void push(T data){
		if(m_size == m_buffersize){
			m_buffersize += m_blocklen;
			T* new_m_h = new T[m_buffersize];
			memmove(new_m_h, m_h, m_size);
			delete m_h;
			m_h = new_m_h;
		}
		
		m_h[m_size] = data;
		adjustBottomToTop(m_size);
		m_size ++;
	}
	
	T pop(){
		if(m_size==0){			
			throw runtime_error("empty heap"); 
		}
		
		T result = m_h[0];
		m_h[0] = m_h[m_size-1];
		m_size--;
		adjustTopToBottom(0); 		
		return result;		
	}	
};


int main(){
	heap<int> h;
	h.push(1);	
	h.push(3);
	h.push(4);
	h.push(2);
	h.push(5);
	
	try{ 
		int re = h.pop();
		while(re){			
			cout << re;
			re = h.pop();
		}
	}catch(exception& e){
		cout << e.what() << endl;
	}
	
	return 0;
}

