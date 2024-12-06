#include <iostream>
#include <stdio.h>
using namespace std;

unsigned factArrayLength(char* stringArr) {
	int length = 0;

	while (stringArr[length]) {
		length++;
	}

	return length;
}

int deletePunctuation(char* arr, char character, char *modifiedArr) {
	int count = 0;
	int indexModifiedArr = 0;
	for (int i = 0; arr[i] != '\0'; i++) {
		if (arr[i] == character) {
			count++;
			if (count <= 1) {
				modifiedArr[indexModifiedArr] = arr[i];
				indexModifiedArr++;
			}
		}
		else {
			modifiedArr[indexModifiedArr] = arr[i];
			indexModifiedArr++;
			count = 0;
		}
		modifiedArr[indexModifiedArr] = '\0';
	}

	return 1;
}

int deleteElipsisMarks(char* arr, char character, char* modifiedArr, int factLength) {
	int count = 0;
	int indexModifiedArr = 0;
	for (int i = 0; i < factLength; i++) {
		if (arr[i] == character) {
			count++;
			if (count <= 3) {
				modifiedArr[indexModifiedArr] = arr[i];
				indexModifiedArr++;
			}
		}
		else {
			modifiedArr[indexModifiedArr] = arr[i];
			indexModifiedArr++;
			count = 0;
		}
		modifiedArr[indexModifiedArr + 1] = '\0';
	}

	return 1;
}

int changeLetterCase(char* arr, int factLength) {
	const int differenceBetweenLettersLatin = 32;

	if (arr[0] >= 97 and arr[0] <= 122)
		arr[0] -= differenceBetweenLettersLatin;

	for (int index = 1; index < factLength - 2; index++) {
		if (arr[index] == ' ' and arr[index - 1] == '.' and arr[index + 1] >= 97 and arr[index + 1] <= 122) {
			arr[index + 1] -= differenceBetweenLettersLatin;
		}

		if (arr[index] == ' ' and arr[index - 1] != '.' and arr[index + 1] >= 65 and arr[index + 1] <= 90) {
			arr[index + 1] += differenceBetweenLettersLatin;
		}

		if (arr[index] != ' ' and (arr[index - 2] != '.' and arr[index - 1] != '.') and arr[index] >= 65 and arr[index] <= 90)
			arr[index] += differenceBetweenLettersLatin;
	}
	return 1;
}

void changeToCapitalLetter(char* arr, int factLength) {
	const int differenceBetweenLettersLatin = 32;
	const int differenceBetweenLettersRussianSecondHalf = 80;

	for (int index = 1; index < factLength; index++) {
		if (arr[index] == ' ') {
			if (arr[index - 1] >= 97 && arr[index - 1] <= 122 or arr[index - 1] >= 160 && arr[index - 1] <= 175)
				arr[index - 1] = arr[index - 1] - differenceBetweenLettersLatin;
			if (arr[index - 1] >= 224 && arr[index - 1] <= 239)
				arr[index - 1] = arr[index - 1] - differenceBetweenLettersRussianSecondHalf;
		}
	}
}

void backwardArrayModification(char* arr, int factLength, char *backwardArray) {
	int index = 0;
	for (int i = factLength - 1; i > -1; i--) {
		backwardArray[index] = arr[i];
		index++;
		backwardArray[index + 1] = '\0';
	}
}

int linearSearch(char* stringArr, char* substringArr) {
	int factLengthStringArr = factArrayLength(stringArr);
	int factLengthSubstringArr = factArrayLength(substringArr);
	int count = 0;

	for (int i = 0; i <= factLengthStringArr - factLengthSubstringArr; i++) {
		int j;
		for (j = 0; j < factLengthSubstringArr; j++) {
			if (stringArr[i + j] != substringArr[j])
				break;
		}

		if (j == factLengthSubstringArr)
			count++;
	}

	return count;
}

int checkWordAmount(char* stringArr, int factLength) {
	bool check = true;
	int index = 0;
	int count = 0;

	for (index = 0; index < factLength; index++) {
		if (stringArr[index] == ' ') {
			if (count >= 10) {
				check = false;
				break;
			}
			count = 0;
		}
		else
			count++;
	}

	if (check != true)
		return -1;
}

int max(int numberOne, int numberTwo) {
	return (numberOne > numberTwo) ? numberOne : numberTwo;
}

void badCharacterHeuristic(char* stringArr, int size, int badCharacter[256]) {
	int i, index;

	for (i = 0; i < 256; i++)
		badCharacter[i] = -1;

	for (i = 0; i < size; i++) {
		index = stringArr[i];
		badCharacter[index] = i;
	}
}

int searchBoyerMoor(char* stringArr, char* substringArr) {
	int factLengthStringArr = factArrayLength(stringArr);
	int factLengthSubstringArr = factArrayLength(substringArr);

	int badCharacter[256];
	int count = 0;

	badCharacterHeuristic(substringArr, factLengthSubstringArr, badCharacter);

	int shift = 0;
	while (shift <= (factLengthStringArr - factLengthSubstringArr)) {
		int j = factLengthSubstringArr - 1;

		while (j >= 0 && substringArr[j] == stringArr[shift + j])
			j--;

		if (j < 0) {
			count++;
			shift += (shift + factLengthSubstringArr < factLengthStringArr) ? factLengthSubstringArr - badCharacter[stringArr[shift + factLengthSubstringArr]] : 1;
		}

		else {
			shift += max(1, j - badCharacter[stringArr[shift + j]]);
		}
	}

	return count;
}

int main()
{
	int const approximateLength = 100;
	char stringArr[approximateLength];
	char finalModification[approximateLength];
	int factLengthFinal, checkCorrectness = 1;

		cout << "Enter your string (!NOTE Your string mast contain 1 to 50 words, and each of them should consist of 1 to 10 letters and/or numbers; the string should end in \".\")" << endl;
		cin.getline(stringArr, approximateLength);
		cin.sync();

		int factLengthString = factArrayLength(stringArr);

		char modifiedArrSpaces[approximateLength];
		deletePunctuation(stringArr, ' ', modifiedArrSpaces);

		char modifiedArrCommas[approximateLength];
		deletePunctuation(modifiedArrSpaces, ',', modifiedArrCommas);

		char modifiedArrExclamationMark[approximateLength];
		deletePunctuation(modifiedArrCommas, '!', modifiedArrExclamationMark);

		char modifiedArrQuestionMark[approximateLength];
		deletePunctuation(modifiedArrExclamationMark, '?', modifiedArrQuestionMark);

		char modifiedArrSlash[approximateLength];
		deletePunctuation(modifiedArrQuestionMark, '/', modifiedArrSlash);

		char modifiedArrColon[approximateLength];
		deletePunctuation(modifiedArrSlash, ':', modifiedArrColon);

		char modifiedArrSemicolon[approximateLength];
		deletePunctuation(modifiedArrColon, ';', modifiedArrSemicolon);

		char modifiedArrRoundBracketLeft[approximateLength];
		deletePunctuation(modifiedArrSemicolon, '(', modifiedArrRoundBracketLeft);

		char modifiedArrRoundBracketRight[approximateLength];
		deletePunctuation(modifiedArrRoundBracketLeft, ')', modifiedArrRoundBracketRight);

		char modifiedArrSquareBracketLeft[approximateLength];
		deletePunctuation(modifiedArrRoundBracketRight, '[', modifiedArrSquareBracketLeft);

		char modifiedArrSquareBracketRight[approximateLength];
		deletePunctuation(modifiedArrSquareBracketLeft, ']', modifiedArrSquareBracketRight);


		char modifiedArrDash[approximateLength];
		deletePunctuation(modifiedArrSquareBracketRight, '-', modifiedArrDash);

		char modifiedArrQuotationMarks[approximateLength];
		deletePunctuation(modifiedArrDash, '\"', modifiedArrQuotationMarks);

		int factLength = factArrayLength(modifiedArrSlash);
		deleteElipsisMarks(modifiedArrSlash, '.', finalModification, factLength);

		factLengthFinal = factArrayLength(finalModification);
		int checkWords = checkWordAmount(finalModification, factLengthFinal);

			changeLetterCase(finalModification, factLengthFinal);


			cout << "Your fixed array looks like: " << endl << finalModification << endl;

			char backwardArray[approximateLength];
			backwardArrayModification(finalModification, factLengthFinal, backwardArray);
			cout << "Your string backwards looks like: " << endl << backwardArray << endl;

			changeToCapitalLetter(backwardArray, factLengthFinal);
			cout << "The backward string with the first letter of each word being turned into a capital one looks like: " << endl << backwardArray << endl;

			cout << "What substring do you want to do find in your string: " << endl;
			char substringArr[approximateLength];
			cin.getline(substringArr, approximateLength);
			cin.sync();

			cout << "Linear Search: " << endl;
			int countLinearSearch = linearSearch(finalModification, substringArr);
			cout << "The amount of times your substring can be found in the string is " << countLinearSearch << endl;

			cout << "Boyer-Moor Search: " << endl;
			int countBoyerMoor = searchBoyerMoor(finalModification, substringArr);
			cout << "The amount of times your substring can be found in the string is " << countBoyerMoor << endl;
	}