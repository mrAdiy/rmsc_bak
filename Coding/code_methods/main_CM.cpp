/*
XXX - номер метода(ов) кодирования
Файлы, которые содержат закодированную информацию, начинаются на cXXX.txt
Файлы, содержащие декодированную информацию, начинаются на dXXX.txt
Файлы, которые содержат ПЕРЕДАННУЮ информацию, начинаются на trXXX.txt

input_data.txt - сырые данные

Немного про размер вх.одных данных:
Трёхмерное дополнение до чётности: 27 бит
Линейный блочный код Хэмминга: 


!!! В main cm_vector.size()-1 - после убрать, т.к. пока только 1 ф-ция из 2 прототипов реализована.
*/
#include <functional>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

//Прототипы НЕ свёрточных ф-ций
//Прототипы ф-ций кодеров
//Первый параметр - файл с названием входа. Второй параметр - файл с
//названием выхода. Оба - без указания расширения (добавляются в ф-ции)
int cm_0(std::string inp, std::string outp); //3D дополнение до чётности. 
int cm_1(std::string inp, std::string outp); //Линейный блочный код Хэмминга.
//Прототипы ф-ций ДЕкодеров
int dm_0(std::string inp, std::string outp); //Трёхмерное дополнение до чётности.
int dm_1(std::string inp, std::string outp); //Линейный блочный код Хэмминга.

//Прототипы свёрточных функций
int crc_convolutional_coder(std::string inp); //Свёртывание с crc
int crc_convolutional_DEcoder(std::string inp); //Свёртывание с crc

//Прототип ф-ции среды передачи.
int transmit(std::string inp, std::string outp);

//Вывод текста в консоль
void sout(std::string str)
{
	std::cout << str << std::endl;
}

//Передача данных!
int transmit(std::string inp, std::string outp){
	std::string Tstr = "DATA/" + inp + ".txt"; //Собираем название файла. 
	std::ifstream in(Tstr);
	std::string Rstr = "DATA/tr" + outp + ".txt";
	std::ofstream out(Rstr, std::ios::out);
	std::string data = "";
	std::vector<bool> DATA;

	while (true){
		in >> data; //Считываем значение из файла.
		if (in.eof()) break; //Конец файла? Выходим из цикла!
		if (data == "1")DATA.push_back(true);
		else DATA.push_back(false);
	}

	//Вносим ошикби!
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

	//Записываем данные, которые "получит" приёмник.
	for (int i = 0; i < DATA.size(); i++) out << DATA[i] << "\n";

	in.close();
	out.close();
	return EXIT_SUCCESS;
}

int main()
{
	sout("TEST START!");

	//Задаём вектор, содержащий все ф-ции, кроме свёрточных.
	std::vector<std::function<int(std::string, std::string)>>
											cm_vector = { cm_0, cm_1 };
	std::vector<std::function<int(std::string, std::string)>>
											dm_vector = { dm_0, dm_1 };
	//Файл с вх. данными: input_data.txt, расширение добавляется в ф-ции.
	std::string input_data = "input_data";

	//Начинаем последовательно вызывать все ф-ции кодирования кроме свёрточных.
	for (int i = 0; i < cm_vector.size()-1; i++){
		//Что-то пошло не так.
		if (cm_vector[i](input_data, std::to_string(i)) == EXIT_FAILURE){
			sout("Some bad things occurs");
			system("pause");
			return EXIT_FAILURE;
		}
	}
	
	//Передаём данные!
	for (int i = 0; i < cm_vector.size()-1; i++){		
		transmit("c" + std::to_string(i), std::to_string(i));
	}
	
	//Начинаем последовательно вызывать все ф-ции ДЕкодирования кроме свёрточных.
	for (int i = 0; i < dm_vector.size()-1; i++){
		//Что-то пошло не так.
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

	std::string str = "DATA/" + inp + ".txt"; //Собираем название файла. 
	std::ifstream in(str);
	std::vector<bool> inp_data; //Вектор, в который считаем наши вх. данные.
	std::vector<bool> res_data; //Вектор, в который кладём закодированные биты.
	bool myBit = true;

	if (!in){ //Проверка на наличие файла
		sout("File open error!");
		return EXIT_FAILURE;
	}

	while (true){
		in >> myBit; //Считываем значение из файла.
		if (in.eof()) break; //Конец файла? Выходим из цикла!
		inp_data.push_back(myBit); //Добавляем считанное значение в вектор.
	}

	//Начинаем кодировать!
	// 1) Заполняем результат битами, которые будем проверять на чётность.
	for (int i = 0; i < inp_data.size(); i++) res_data.push_back(inp_data[i]);
	// 2) Начинаем собирать ПРОВЕРОЧНЫЕ биты по СЛОЯМ.
	for (int i = 0; i < inp_data.size(); i += 9){ //Берём блоки по 9
		//Работа с блоком!
		//Сначала - по строкам
		for (int j = i; j < i + 9; j += 3){
			myBit = res_data[j] ^ res_data[j + 1] ^ res_data[j + 2];
			res_data.push_back(myBit);
		}
		//Потом - по столбцам
		for (int j = i; j < i + 3; j++){
			myBit = res_data[j] ^ res_data[j + 3] ^ res_data[j + 6];
			res_data.push_back(myBit);
		}
	}
	 // 3) Начинаем собирать ПРОВЕРОЧНЫЕ биты по ГЛУБИНЕ.
	 for (int i = 0; i < 9; i++){ //Берём целые слои
		 myBit = res_data[i] ^ res_data[i + 9] ^ res_data[i + 18];
		 res_data.push_back(myBit);
	 }

	for (int i = 0; i < res_data.size(); i += 3)
		std::cout << res_data[i] << res_data[i + 1] << res_data[i + 2] << " ";

	in.close();

	//Сохраняем полученный код
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

	std::string str = "DATA/" + inp + ".txt"; //Собираем название файла. 
	std::ifstream in(str);
	std::vector<bool> inp_data; //Вектор, в который считаем наши вх. данные.
	std::vector<bool> res_data; //Вектор, в который кладём закодированные биты.
	bool myBit = true;

	if (!in){ //Проверка на наличие файла
		sout("File open error!");
		return EXIT_FAILURE;
	}

	while (true){
		in >> myBit; //Считываем значение из файла.
		if (in.eof()) break; //Конец файла? Выходим из цикла!
		inp_data.push_back(myBit); //Добавляем считанное значение в вектор.
	}

	//Начинаем кодировать!
	// ...
	
	//Сохраняем полученный код
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

	std::string str = "DATA/" + inp + ".txt"; //Собираем название файла. 
	std::ifstream in(str);
	std::vector<bool> inp_data; //Вектор, в который считаем наши вх. данные.
	std::vector<bool> check_data; //Вектор, в который считаем наши вх. данные.
	std::vector<bool> control_data; //Вектор, в который считаем наши вх. данные.
	std::vector<bool> check_bits; //Вектор, в который кладём проверочные биты.
	std::vector<bool> res_data; //Вектор, в который кладём ДЕкодированные биты.
	int control_row_index = 0, control_column_index = 3;
	int total_err_counter = 0, temp = 0, layer_offset = 0;

	bool myBit = true;

	if (!in){ //Проверка на наличие файла
		sout("File open error!");
		return EXIT_FAILURE;
	}

	while (true){
		in >> myBit; //Считываем значение из файла.
		if (in.eof()) break; //Конец файла? Выходим из цикла!
		inp_data.push_back(myBit); //Добавляем считанное значение в вектор.
	}

	//Начинаем ДЕдировать!
	// 1) Заполняем результат битами, которые будем проверять на чётность.
	for (int i = 0; i < 27; i++) check_data.push_back(inp_data[i]);
	// 2) Заполняем принятые контрольные биты.
	for (int i = 27; i < inp_data.size(); i++) control_data.push_back(inp_data[i]);
	// 3) Строим матрицу проверки для каждого слоя
	for (int i = 0; i < check_data.size(); i += 9) {
		//Сначала - по строкам
		for (int j = i; j < i + 9; j += 3){
			myBit = check_data[j] ^ check_data[j + 1] ^ check_data[j + 2] 
				^ control_data[control_row_index];
			control_row_index++;
			check_bits.push_back(myBit); 
		}
		control_row_index += 3;
		//Потом - по столбцам
		for (int j = i; j < i + 3; j++){
			myBit = check_data[j] ^ check_data[j + 3] ^ check_data[j + 6] 
				^ control_data[control_column_index];
			control_column_index++;
			check_bits.push_back(myBit);
		}
		control_column_index += 3;
	}
	// 4) Строим матрицу проверки по глубине
	for (int i = 0; i < 9; i++){ //Берём целые слои
		myBit = check_data[i] ^ check_data[i + 9] ^ check_data[i + 18]
			^ control_data[18+i];
		check_bits.push_back(myBit);
	}
	// 5) Приступаем к определению и исправлению ошибок!

	for (int i = 0; i < 18; i++)std::cout << check_bits[i]; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	std::cout << " ";
	for (int i = 18; i < 27; i++)std::cout << check_bits[i];
	std::cout << std::endl;

	//Сначала проверка на ОДИНОЧНЫЕ ошибки
	layer_offset = 0;
	for (int i = 0; i < 18; i+=6){ //Каждая итерация - новый слой.

		temp = 0; //В новом слое ищем ошибки, словно их не было ранее.
		//Удостоверимся, что ошибка есть только в одной из строк, а после - что
		//только в одном из столбцов в исследуемом слое.
		for (int j = i; j < i + 3; j++) if (check_bits[j] == true) temp++;
		if (temp == 2) continue;
		if (temp == 1) 
			for (int j = i + 3; j < i + 6; j++) if (check_bits[j] == true) temp++;
		else continue; //Данная часть декодирования не поможет!
		
		if (temp != 2) continue; //Б.м. ошибок>1 - идём дальше.
		else{//Всего 1 ошибка - исправляем её!
			total_err_counter++;			
			for (int r = i; r < i+3; r++){ //Строки
				for (int c = i+3; c < i+6; c++){ //Столбцы
					if (check_bits[r] == true && check_bits[c]==true){
						temp = (r * 3 + c - 3)-15*layer_offset;//Индекс внутри слоя.
						
						inp_data[temp] = !inp_data[temp];
					}
				}
			}
		}
		layer_offset++; //Переходим к следующему слою.
	}

	//Проверка на ПАРНЫЕ ошибки в одном столбце/одной строке.
	layer_offset = 0;
	for (int i = 0; i < 18; i += 6){ //Каждая итерация - новый слой.
		temp = 0;
		if (total_err_counter != 0) break; //Уже была найдена единичная ошибка
		//(или даже не одна). Ничего не сделать данным способом.
		
		//Две ошибки в  СТРОКЕ.
		for (int j = i; j < i + 3; j++) if (check_bits[j] == true) temp++;
		if (temp == 2){
			temp = 0; 
			for (int j = i+3; j < i + 6; j++) if (check_bits[j] == true) temp++;
			if (temp != 0) break; //Другой случай.
			total_err_counter += 2;
		}
		//Две ошибки в СТОЛБЦЕ.
		if (temp==0) 
			for (int j = i+3; j < i + 6; j++) if (check_bits[j] == true)temp++;
		if (temp == 2){
			temp = 0;
			for (int j = i; j < i + 3; j++) if (check_bits[j] == true) temp++;
			if (temp != 0) break; //Другой случай.
			total_err_counter += 2;
		} 
		
		//В данном слое ошибок нет: проверяем дальше!
		if (total_err_counter != 2){
			layer_offset++; //Переходим к следующему слою.
			continue; 
		}
		
		temp = 0;
		for (int i = 18; i < 27; i++) if (check_bits[i] == true) temp++;
		if (temp != 2) break; //В матрице по глубине указано не 2 повреждения - 
		// - ничего не сделать данным способом.

		//Теперь мы точно знаем, что у нас по ошибке в строке или столбце.
		//Просто накладываем матрицу "по глубине"
		for (int i = 18; i < 27; i++) if (check_bits[i] == true){
				temp = i + 9 * layer_offset - 18;
				inp_data[temp] = !inp_data[temp];				
			}
	}

	//Общий случай!
	std::vector<std::vector<int>> error_map;
	/*
	error_map.push_back({1, 2, 3});
	for (int i = 0; i < error_map.size(); i++)
	{
		std::cout << error_map[i][0] << error_map[i][1] << error_map[i][2];
	}
	*/

	//Сохраняем полученный код !!!
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

	std::string str = "DATA/" + inp + ".txt"; //Собираем название файла. 
	std::ifstream in(str);
	std::vector<bool> inp_data; //Вектор, в который считаем наши вх. данные.
	std::vector<bool> res_data; //Вектор, в который кладём закодированные биты.
	bool myBit = true;

	if (!in){ //Проверка на наличие файла
		sout("File open error!");
		return EXIT_FAILURE;
	}

	while (true){
		in >> myBit; //Считываем значение из файла.
		if (in.eof()) break; //Конец файла? Выходим из цикла!
		inp_data.push_back(myBit); //Добавляем считанное значение в вектор.
	}

	//Начинаем кодировать!
	// ...

	//Сохраняем полученный код
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