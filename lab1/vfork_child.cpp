#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
int main(){
	int parent_id = getpid();
	int grand_child_id[4];

	cout<<"Parent Id :"<<parent_id<<endl;

	int child1_id = vfork();

	if(child1_id < 0){
		cout<<"Fork Error\n";
	}else if(child1_id == 0){
		cout<<"Child 1 Id : "<<getpid()<<endl;
		int grand_child = vfork();

		if(grand_child < 0){
			cout<<"Fork Error\n";
		}else if(grand_child == 0){
			grand_child_id[0] = getpid();
			_exit(0);
		}else{
			grand_child = vfork();

			if(grand_child < 0){
				cout<<"Fork Error\n";
			}else if(grand_child == 0){
				grand_child_id[1] = getpid();
				_exit(0);
			}else{
				_exit(0);
			}
		}
	}else{
			int child2_id = vfork();

			if(child2_id < 0){
				cout<<"Fork Error\n";
			}else if(child2_id == 0){
				cout<<"Child 2 Id : "<<getpid()<<endl;

				int grand_child = vfork();

				if(grand_child < 0){
					cout<<"Fork Error\n";
				}else if(grand_child == 0){
					grand_child_id[2] = getpid();
					_exit(0);
				}else{
					grand_child = vfork();

					if(grand_child < 0){
						cout<<"Fork Error\n";
					}else if(grand_child == 0){
						grand_child_id[3] = getpid();
						_exit(0);
					}else{
						_exit(0);
					}
				}
			}else{
				for(int i=0;i<4;i++){
					cout<<"GrandChild Id :"<<grand_child_id[i]<<endl;
				}
				exit(0);
			}
	}
}