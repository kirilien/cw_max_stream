#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include "list_funcs.h"
#include "edge.h"

#include <cstdlib>
using namespace std;

class ford_falkerson {
private:
List<string> list_recs;
	List<edge> list_edges;

	List<string> list_nodes;
	int source;
	int sink;
	int **matrix_adj;
public:
	int maxflow;
	
	ford_falkerson() {

	}
	ford_falkerson(List<string> *ini_list) {
		this->list_recs = *ini_list;
		string temp_rec, start, finish, capacity;
		int cap, sublen, count_rev=1;
		bool fl_double_dir;
		for (int i = 0; i < list_recs.get_size(); i++) {
			fl_double_dir = 0;
			edge temp_edge;
			temp_rec = list_recs.at(i);
			//staring point
			sublen = temp_rec.find_first_of(" ");
			start = temp_rec.substr(0, sublen);
			temp_rec.erase(0, sublen + 1);
			//finishing point
			sublen = temp_rec.find_first_of(" ");
			finish = temp_rec.substr(0, sublen);
			temp_rec.erase(0, sublen + 1);
			//its capacity
			capacity = temp_rec;
			cap = atoi(capacity.c_str());
			//if there is double-directed edge in graph
			for (int j = 0; j < list_edges.get_size(); j++) 
				if ((list_edges.at(j).start == finish) && (list_edges.at(j).finish == start)) {
					fl_double_dir = 1;
					
					string intermed = "V" + to_string(count_rev);
					temp_edge.start = start;
					temp_edge.finish = intermed;
					temp_edge.capacity = cap;
					list_edges.push_back(temp_edge);
					temp_edge.start = intermed;
					temp_edge.finish = finish;
					temp_edge.capacity = cap;
					list_edges.push_back(temp_edge);
					count_rev++;
				}
			if (!fl_double_dir) {
				//forming edge, pushing it in list
				temp_edge.start = start;
				temp_edge.finish = finish;
				temp_edge.capacity = cap;
				list_edges.push_back(temp_edge);
			}
		}
		//forming indexing list for matrix----------------------------------------------
		cout << " ";//for clear printing matrix, it's to remove
		for (int i = 0; i < list_edges.get_size(); i++) {
			
			if (!list_nodes.isThere(list_edges.at(i).start)) {
				list_nodes.push_back(list_edges.at(i).start);
				cout<< " " << list_edges.at(i).start ;//for clear printing matrix, it's to remove
				if (list_edges.at(i).start == "S")
					source = list_nodes.get_size() - 1;
			}

			if (!list_nodes.isThere(list_edges.at(i).finish)){
				list_nodes.push_back(list_edges.at(i).finish);
				cout<< " " << list_edges.at(i).finish ;//for clear printing matrix, it's to remove
				if (list_edges.at(i).finish == "T")
					sink = list_nodes.get_size() - 1;
			}
		}
		cout << "\n";
		//forming matrix
		matrix_adj = new int*[list_nodes.get_size()];
		for (int i = 0; i < list_nodes.get_size(); i++)
			matrix_adj [i]=new int [list_nodes.get_size()];
		for (int i = 0; i < list_nodes.get_size(); i++)
			for (int j = 0; j < list_nodes.get_size(); j++)
				matrix_adj[i][j] = 0;
		//filling the matrix up
		for (int i = 0; i < list_edges.get_size(); i++) {
			int from, to;
			for (int j = 0; j < list_nodes.get_size(); j++) {
				if (list_nodes.at(j) == list_edges.at(i).start)
					from = j;
				if (list_nodes.at(j) == list_edges.at(i).finish)
					to = j;
			}
			matrix_adj[from][to] = list_edges.at(i).capacity;
			matrix_adj[to][from] = 0;

		}
		//printing the matrix, it's to remove
		for (int i = 0; i < list_nodes.get_size(); i++) {
			cout << list_nodes.at(i) << " ";
			for (int j = 0; j < list_nodes.get_size(); j++)
				cout << matrix_adj[i][j] << " ";
			cout<< "\n";
		}
		bool flag = 1;
		maxflow = 0;
		while (flag) {
			bool *visited = new bool[list_nodes.get_size()];
			for (int i = 0; i < list_nodes.get_size(); i++)
				visited[i] = 0;
			int currflow = newflow(source, 100000, visited);

			maxflow += currflow;
			flag = currflow;
			delete[] visited;
		}
		

		
	}
	int newflow(int surs, int cmin, bool *vis_orig) {
		if (surs == sink)
			return cmin;
		bool *vis_loc = new bool[list_nodes.get_size()];
		for (int i = 0; i < list_nodes.get_size(); i++)
			vis_loc[i] = vis_orig[i];
		vis_loc[surs] = 1;
		//searching for positive flow way
		for (int i = 0; i < list_nodes.get_size(); i++)
			if ((matrix_adj[surs][i] > 0) && (!vis_loc[i])) {
				//even if algorithm will get in a buffer node of double-directed edge
				//it will work correctly, because there is only one enter and one exit from buffer
				int delta = newflow(i, min(cmin, matrix_adj[surs][i]), vis_loc);
				if (delta > 0) {
					matrix_adj[surs][i] -= delta;
					matrix_adj[i][surs] += delta;
					delete [] vis_loc;
					return delta;
					
				}
			}
		return 0;
	}


		
		



	~ford_falkerson() {
		for (int i = 0; i < list_nodes.get_size(); i++)
			delete[]matrix_adj[i];
	}
};