/*
XXX - ����� ������(��) �����������
�����, ������� �������� �������������� ����������, ���������� �� cXXX.txt
�����, ���������� �������������� ����������, ���������� �� dXXX.txt
�����, ������� �������� ���������� ����������, ���������� �� trXXX.txt

input_data.txt - ����� ������

������� ��� ������ ��.����� ������:
��������� ���������� �� ��������: 27 ���
�������� ������� ��� ��������: 


!!! � main cm_vector.size()-1 - ����� ������, �.�. ���� ������ 1 �-��� �� 2 ���������� �����������.
*/
#include <functional>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

//��������� �� ��������� �-���
//��������� �-��� �������
//������ �������� - ���� � ��������� �����. ������ �������� - ���� �
//��������� ������. ��� - ��� �������� ���������� (����������� � �-���)
int cm_0(std::string inp, std::string outp); //3D ���������� �� ��������. 
int cm_1(std::string inp, std::string outp); //�������� ������� ��� ��������.
//��������� �-��� ���������
int dm_0(std::string inp, std::string outp); //��������� ���������� �� ��������.
int dm_1(std::string inp, std::string outp); //�������� ������� ��� ��������.

//��������� ��������� �������
int crc_convolutional_coder(std::string inp); //���������� � crc
int crc_convolutional_DEcoder(std::string inp); //���������� � crc

//�������� �-��� ����� ��������.
int transmit(std::string inp, std::string outp);

//����� ������ � �������
void sout(std::string str)
{
	std::cout << str << std::endl;
}

//�������� ������!
int transmit(std::string inp, std::string outp){
	std::string Tstr = "DATA/" + inp + ".txt"; //�������� �������� �����. 
	std::ifstream in(Tstr);
	std::string Rstr = "DATA/tr" + outp + ".txt";
	std::ofstream out(Rstr, std::ios::out);
	std::string data = "";
	std::vector<bool> DATA;

	while (true){
		in >> data; //��������� �������� �� �����.
		if (in.eof()) break; //����� �����? ������� �� �����!
		if (data == "1")DATA.push_back(true);
		else DATA.push_back(false);
	}

	//������ ������!
	/*
	DATA[3] = !DATA[3];
	DATA[12] = !DATA[12];
	DATA[21] = !DATA[21];
	*/
	/*
	DATA[24] = !DATA[24];
	DATA[21] = !DATA[21];
	*/

	DATA[10] = !DATA[10];
	DATA[12] = !DATA[12];
	DATA[15] = !DATA[15];

	//���������� ������, ������� "�������" �������.
	for (int i = 0; i < DATA.size(); i++) out << DATA[i] << "\n";

	in.close();
	out.close();
	return EXIT_SUCCESS;
}

int main()
{
	sout("TEST START!");

	//����� ������, ���������� ��� �-���, ����� ���������.
	std::vector<std::function<int(std::string, std::string)>>
											cm_vector = { cm_0, cm_1 };
	std::vector<std::function<int(std::string, std::string)>>
											dm_vector = { dm_0, dm_1 };
	//���� � ��. �������: input_data.txt, ���������� ����������� � �-���.
	std::string input_data = "input_data";

	//�������� ��������������� �������� ��� �-��� ����������� ����� ���������.
	for (int i = 0; i < cm_vector.size()-1; i++){
		//���-�� ����� �� ���.
		if (cm_vector[i](input_data, std::to_string(i)) == EXIT_FAILURE){
			sout("Some bad things occurs");
			system("pause");
			return EXIT_FAILURE;
		}
	}
	
	//������� ������!
	for (int i = 0; i < cm_vector.size()-1; i++){		
		transmit("c" + std::to_string(i), std::to_string(i));
	}
	
	//�������� ��������������� �������� ��� �-��� ������������� ����� ���������.
	for (int i = 0; i < dm_vector.size()-1; i++){
		//���-�� ����� �� ���.
		if (dm_vector[i]("tr" + std::to_string(i), std::to_string(i)) == EXIT_FAILURE){
			sout("Some bad things occurs");
			system("pause");
			return EXIT_FAILURE;
		}
	}

	sout("\n\nTEST END!");
	system("pause");
	return EXIT_SUCCESS;
}

int cm_0(std::string inp, std::string outp)
{
	sout("\n\n[CODE] METHOD: 3D parity control");

	std::string str = "DATA/" + inp + ".txt"; //�������� �������� �����. 
	std::ifstream in(str);
	std::vector<bool> inp_data; //������, � ������� ������� ���� ��. ������.
	std::vector<bool> res_data; //������, � ������� ����� �������������� ����.
	bool myBit = true;

	if (!in){ //�������� �� ������� �����
		sout("File open error!");
		return EXIT_FAILURE;
	}

	while (true){
		in >> myBit; //��������� �������� �� �����.
		if (in.eof()) break; //����� �����? ������� �� �����!
		inp_data.push_back(myBit); //��������� ��������� �������� � ������.
	}

	//�������� ����������!
	// 1) ��������� ��������� ������, ������� ����� ��������� �� ��������.
	for (int i = 0; i < inp_data.size(); i++) res_data.push_back(inp_data[i]);
	// 2) �������� �������� ����������� ���� �� �����.
	for (int i = 0; i < inp_data.size(); i += 9){ //���� ����� �� 9
		//������ � ������!
		//������� - �� �������
		for (int j = i; j < i + 9; j += 3){
			myBit = res_data[j] ^ res_data[j + 1] ^ res_data[j + 2];
			res_data.push_back(myBit);
		}
		//����� - �� ��������
		for (int j = i; j < i + 3; j++){
			myBit = res_data[j] ^ res_data[j + 3] ^ res_data[j + 6];
			res_data.push_back(myBit);
		}
	}
	 // 3) �������� �������� ����������� ���� �� �������.
	 for (int i = 0; i < 9; i++){ //���� ����� ����
		 myBit = res_data[i] ^ res_data[i + 9] ^ res_data[i + 18];
		 res_data.push_back(myBit);
	 }

	for (int i = 0; i < res_data.size(); i += 3)
		std::cout << res_data[i] << res_data[i + 1] << res_data[i + 2] << " ";

	in.close();

	//��������� ���������� ���
	str = "DATA/c" + outp + ".txt";
	std::ofstream out(str, std::ios::out);
	for (int i = 0; i < res_data.size(); i++)
		out << res_data[i] << "\n";
	out.close();

	return EXIT_SUCCESS;
}

int cm_1(std::string inp, std::string outp)
{
	sout("\n\n[CODE] METHOD: Hamming linear block code");

	std::string str = "DATA/" + inp + ".txt"; //�������� �������� �����. 
	std::ifstream in(str);
	std::vector<bool> inp_data; //������, � ������� ������� ���� ��. ������.
	std::vector<bool> res_data; //������, � ������� ����� �������������� ����.
	bool myBit = true;

	if (!in){ //�������� �� ������� �����
		sout("File open error!");
		return EXIT_FAILURE;
	}

	while (true){
		in >> myBit; //��������� �������� �� �����.
		if (in.eof()) break; //����� �����? ������� �� �����!
		inp_data.push_back(myBit); //��������� ��������� �������� � ������.
	}

	//�������� ����������!
	// ...
	
	//��������� ���������� ���
	str = "DATA/c" + outp + ".txt";
	std::ofstream out(str, std::ios::out);
	for (int i = 0; i < res_data.size(); i++)
		out << res_data[i] << "\n";
	out.close();

	return EXIT_SUCCESS;
}

int dm_0(std::string inp, std::string outp)
{
	sout("\n\n[DEcode] METHOD: 3D parity control");

	std::string str = "DATA/" + inp + ".txt"; //�������� �������� �����. 
	std::ifstream in(str);
	std::vector<bool> inp_data; //������, � ������� ������� ���� ��. ������.
	std::vector<bool> check_data; //������, � ������� ������� ���� ��. ������.
	std::vector<bool> control_data; //������, � ������� ������� ���� ��. ������.
	std::vector<bool> check_bits; //������, � ������� ����� ����������� ����.
	std::vector<bool> res_data; //������, � ������� ����� �������������� ����.
	int control_row_index = 0, control_column_index = 3;
	int total_err_counter = 0, temp = 0, layer_offset = 0;

	bool myBit = true;

	if (!in){ //�������� �� ������� �����
		sout("File open error!");
		return EXIT_FAILURE;
	}

	while (true){
		in >> myBit; //��������� �������� �� �����.
		if (in.eof()) break; //����� �����? ������� �� �����!
		inp_data.push_back(myBit); //��������� ��������� �������� � ������.
	}

	//�������� ����������!
	// 1) ��������� ��������� ������, ������� ����� ��������� �� ��������.
	for (int i = 0; i < 27; i++) check_data.push_back(inp_data[i]);
	// 2) ��������� �������� ����������� ����.
	for (int i = 27; i < inp_data.size(); i++) control_data.push_back(inp_data[i]);
	// 3) ������ ������� �������� ��� ������� ����
	for (int i = 0; i < check_data.size(); i += 9) {
		//������� - �� �������
		for (int j = i; j < i + 9; j += 3){
			myBit = check_data[j] ^ check_data[j + 1] ^ check_data[j + 2] 
				^ control_data[control_row_index];
			control_row_index++;
			check_bits.push_back(myBit); 
		}
		control_row_index += 3;
		//����� - �� ��������
		for (int j = i; j < i + 3; j++){
			myBit = check_data[j] ^ check_data[j + 3] ^ check_data[j + 6] 
				^ control_data[control_column_index];
			control_column_index++;
			check_bits.push_back(myBit);
		}
		control_column_index += 3;
	}
	// 4) ������ ������� �������� �� �������
	for (int i = 0; i < 9; i++){ //���� ����� ����
		myBit = check_data[i] ^ check_data[i + 9] ^ check_data[i + 18]
			^ control_data[18+i];
		check_bits.push_back(myBit);
	}
	// 5) ���������� � ����������� � ����������� ������!

	for (int i = 0; i < 18; i++)std::cout << check_bits[i]; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	std::cout << " ";
	for (int i = 18; i < 27; i++)std::cout << check_bits[i];
	std::cout << std::endl;

	//������� �������� �� ��������� ������
	layer_offset = 0;
	for (int i = 0; i < 18; i+=6){ //������ �������� - ����� ����.

		temp = 0; //� ����� ���� ���� ������, ������ �� �� ���� �����.
		//�������������, ��� ������ ���� ������ � ����� �� �����, � ����� - ���
		//������ � ����� �� �������� � ����������� ����.
		for (int j = i; j < i + 3; j++) if (check_bits[j] == true) temp++;
		if (temp == 2) continue;
		if (temp == 1) 
			for (int j = i + 3; j < i + 6; j++) if (check_bits[j] == true) temp++;
		else continue; //������ ����� ������������� �� �������!
		
		if (temp != 2) continue; //�.�. ������>1 - ��� ������.
		else{//����� 1 ������ - ���������� �!
			total_err_counter++;			
			for (int r = i; r < i+3; r++){ //������
				for (int c = i+3; c < i+6; c++){ //�������
					if (check_bits[r] == true && check_bits[c]==true){
						temp = (r * 3 + c - 3)-15*layer_offset;//������ ������ ����.
						
						inp_data[temp] = !inp_data[temp];
					}
				}
			}
		}
		layer_offset++; //��������� � ���������� ����.
	}

	//�������� �� ������ ������ � ����� �������/����� ������.
	layer_offset = 0;
	for (int i = 0; i < 18; i += 6){ //������ �������� - ����� ����.
		temp = 0;
		if (total_err_counter != 0) break; //��� ���� ������� ��������� ������
		//(��� ���� �� ����). ������ �� ������� ������ ��������.
		
		//��� ������ �  ������.
		for (int j = i; j < i + 3; j++) if (check_bits[j] == true) temp++;
		if (temp == 2){
			temp = 0; 
			for (int j = i+3; j < i + 6; j++) if (check_bits[j] == true) temp++;
			if (temp != 0) break; //������ ������.
			total_err_counter += 2;
		}
		//��� ������ � �������.
		if (temp==0) 
			for (int j = i+3; j < i + 6; j++) if (check_bits[j] == true)temp++;
		if (temp == 2){
			temp = 0;
			for (int j = i; j < i + 3; j++) if (check_bits[j] == true) temp++;
			if (temp != 0) break; //������ ������.
			total_err_counter += 2;
		} 
		
		//� ������ ���� ������ ���: ��������� ������!
		if (total_err_counter != 2){
			layer_offset++; //��������� � ���������� ����.
			continue; 
		}
		
		temp = 0;
		for (int i = 18; i < 27; i++) if (check_bits[i] == true) temp++;
		if (temp != 2) break; //� ������� �� ������� ������� �� 2 ����������� - 
		// - ������ �� ������� ������ ��������.

		//������ �� ����� �����, ��� � ��� �� ������ � ������ ��� �������.
		//������ ����������� ������� "�� �������"
		for (int i = 18; i < 27; i++) if (check_bits[i] == true){
				temp = i + 9 * layer_offset - 18;
				inp_data[temp] = !inp_data[temp];				
			}
	}

	//����� ������!
	std::vector<std::vector<int>> error_map;
	/*
	error_map.push_back({1, 2, 3});
	for (int i = 0; i < error_map.size(); i++)
	{
		std::cout << error_map[i][0] << error_map[i][1] << error_map[i][2];
	}
	*/

	//��������� ���������� ��� !!!
	for (int i = 0; i < 27; i++) res_data.push_back(inp_data[i]);
	str = "DATA/d" + outp + ".txt";
	std::ofstream out(str, std::ios::out);
	for (int i = 0; i < res_data.size(); i++)
		out << res_data[i] << "\n";
	out.close();

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	sout("");
	for (int i = 0; i < res_data.size(); i += 3)
		std::cout << res_data[i] << res_data[i + 1] << res_data[i + 2] << " ";

	return EXIT_SUCCESS;
}

int dm_1(std::string inp, std::string outp)
{
	sout("\n\n[DEcode] METHOD: Hamming linear block code");

	std::string str = "DATA/" + inp + ".txt"; //�������� �������� �����. 
	std::ifstream in(str);
	std::vector<bool> inp_data; //������, � ������� ������� ���� ��. ������.
	std::vector<bool> res_data; //������, � ������� ����� �������������� ����.
	bool myBit = true;

	if (!in){ //�������� �� ������� �����
		sout("File open error!");
		return EXIT_FAILURE;
	}

	while (true){
		in >> myBit; //��������� �������� �� �����.
		if (in.eof()) break; //����� �����? ������� �� �����!
		inp_data.push_back(myBit); //��������� ��������� �������� � ������.
	}

	//�������� ����������!
	// ...

	//��������� ���������� ���
	for (int i = 0; i < 27; i++) res_data.push_back(inp_data[i]);
	str = "DATA/d" + outp + ".txt";
	std::ofstream out(str, std::ios::out);
	for (int i = 0; i < res_data.size(); i++)
		out << res_data[i] << "\n";
	out.close();

	return EXIT_SUCCESS;
}

int crc_convolutional_coder(std::string inp, std::string outp)
{
	sout("\n\n[CODE] METHOD: Convolutional crc code");
	return EXIT_SUCCESS;
}
int crc_convolutional_DEcoder(std::string inp, std::string outp)
{
	sout("\n\n[DEcode] METHOD: Convolutional crc code");
	return EXIT_SUCCESS;
}