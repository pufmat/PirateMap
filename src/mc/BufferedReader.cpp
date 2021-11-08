#include "BufferedReader.h"

BufferedReader::BufferedReader(std::function<void()> request){
	this->request = request;

	this->buffer = nullptr;
	this->size = 0;

	this->cursor = 0;
}

void BufferedReader::setBuffer(byte* buffer, std::size_t size){
	this->buffer = buffer;
	this->size = size;

	this->cursor = 0;
}

byte BufferedReader::read(){
	if(cursor == size){
		request();
	}
	return buffer[cursor++];
}

BufferedReader::~BufferedReader(){

}

