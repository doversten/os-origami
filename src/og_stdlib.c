int og_parse_int(char* text, int* n) {
	int i = 0;
	int ack = 0;

	if (!((text[0] >= '0' && text[0] <= '9') || text[0] == '-')) {
		return -1;
	}

	if (text[0] == '-') {
		i++;
	}

	while(text[i]) {
		if (text[i] >= '0' && text[i] <= '9') {
			ack = ack * 10 + (text[i] - '0');
			i++;
		} else {
			return -1;
		}
	}

	if (text[0] == '-') {
		ack *= -1;
		// This is reALLY A LOT MORE INTUATIVE
		//ack = ack + (2147483647 - (ack-1)) + (2147483647 - (ack-1));
	}

	*n = ack;
	return 0;

}

int og_string_equals(char* a, char* b) {
	
	int i = 0;
	while(a[i] && b[i]){
		if (a[i] != b[i]){
			return 0;	// The current characters are not equal
		}
		i++;
	}
	
	if (a[i] || b[i]) {		// One of the string is longer then the other
		return 0;
	}

	return 1;
}

void og_string_concat(char *buffer, char *a, char *b) {
	int i = 0;
	int j = 0;
	while(a[i]) {
		buffer[j] = a[i];
		i++;
		j++;
	}
	i = 0;
	while(b[i]) {
		buffer[j] = b[i];
		i++;
		j++;
	}
	buffer[j] = 0;
}

void og_int_to_string(char *buffer, int i) {
	int length = 0;
	int reminder = i;

	if(i == 0) {
		buffer[0] = '0';
		buffer[1] = 0;
		return;
	}

	while(reminder > 0) {
		length++;
		reminder /= 10;
	}
	buffer[length] = 0;
	while(length > 0) {
		buffer[length-1] = '0' + (i % 10);
		i /= 10;
		length--;
	}
}
