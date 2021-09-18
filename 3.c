#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
typedef struct node* p_node;
typedef struct node {
	int value;
	struct node* p_next;
}node;
typedef struct gycchang {
	int m_len;
	int m_max_len;
	int m_count;//1초가 지날때마다 실행하면서 증가시킬 멤버변수
	char* message;
}gycchang;
typedef struct gycchang* p_gyc;
#define BUF_SIZE 44
void Init(void* const p, char flag);
char* SetString_ori(struct gycchang* p_gyc, const char* ap_message);//원래 변수에 strcat으로 문자열 붙여넣기를 통해 반환
char* SetString_new(struct gycchang* p_gyc, const char* ap_message);//새로운 변수에 strcat으로 문자열붙여넣기를 통해 반환
void Init(void* const p, char flag)
{
	if (flag) {
		((p_gyc)p)->m_len = 1;
		printf("%p : (gycchang*)p, %p : &((gycchang*)p)->m_max_len)\n", (p_gyc)p, &((gycchang*)p)->m_max_len);//m_len 요소 초기화 후 구조체 변수 시작 주소와 이 변수 주소를 출력해봄
		((p_gyc)p)->m_max_len = 1;
		((p_gyc)p)->m_count = 0;
		((p_gyc)p)->message = NULL;
		((p_gyc)p)->message = (char*)malloc(1);
		((p_gyc)p)->message = 0;
	}
}
void GetInfo(struct gycchang* p_gyc)
{
	struct gycchang *p;
	p = p_gyc;
	printf("%d %d %s\n", p->m_len, p->m_max_len, p->message);
}
char* method1(const char(*ap_str)[BUF_SIZE])
{
	char *p_tmp_array = (char*)malloc(BUF_SIZE);
	char tmp_array[BUF_SIZE] = { 0, };
	strcpy_s(tmp_array, BUF_SIZE, *ap_str);
	p_tmp_array = tmp_array;
	return p_tmp_array;
}
//널문자를 전달하지 않고 널문자를 배열을 전달받은 함수에서 붙여서 printf해주는 코드
//char*형 반환이여도 char형 배열을 반환해도 정상작동합니다
char* method2(char(*ptr)[BUF_SIZE], int str_len)
{
	//확인(널문자를 제외하고 넘어와도 정상작동하는지 확인하려고 int형 변수를 매개변수로 받아서 확인해본 것이다)
	printf("str_len %d = strlen(*ptr) %d\n", str_len, strlen(*ptr));
	//널문자를 붙이는 작업
	//*ptr = *(ptr+0) : 문자열 시작주소
	//[BUF_SIZE-1] : 마지막 인덱스에 널문자를 넣어준다
	(*ptr)[BUF_SIZE - 1] = '\0';
	printf("%s : 널문자를 붙인 문자열로 출력해야 정상작동합니다\n", *ptr);
	return *ptr;
}
char* IntToBuf(int i)
{
	char* Buf = (char*)malloc(1);
	sprintf(Buf, "%d", i);
	return Buf;
}
char* SetString_ori(struct gycchang* p_gyc, const char* ap_message)
{ 
	char ori[BUF_SIZE];
	
	char temp_left[BUF_SIZE] = {0,};//18글자(글자+띄어쓰기용 공백문자)//after connection, (공백까지포함)(18글자)+strcat으로 붙일 길이(1+21)+널문자용(1바이트) = 41
	char temp_right[22];//21글자+1바이트(널문자)//second(s) has passed.(21글자)
	char ins[1] = { 0, };//숫자를 문자열로 바꾼 것을 저장할 배열//-127~128까지 저장가능//정수형 문자열의 정수가 1~5를 넣을 거라서 이걸로 충분
	int total_size = strlen(temp_left) + 1;
	//const int limit = BUF_SIZE;
	char m_message[BUF_SIZE];

	if (p_gyc == NULL) {
		p_gyc = (struct gycchang*)malloc(sizeof(gycchang));
		total_size = strlen(ap_message) + 1;//<=44
		p_gyc->message = (char*)malloc(total_size);
	}
	else {
		total_size = strlen(ap_message) + 1;
		p_gyc->message = (char*)realloc(p_gyc->message,total_size);
	}
	p_gyc->m_max_len=total_size;
	p_gyc->m_len = total_size;
	const char tmp[BUF_SIZE] = "after connection, second(s) has passed.";
	char* r_ori = (char*)malloc(BUF_SIZE);
	r_ori = method1(&tmp);
	strcpy_s(ori, BUF_SIZE, r_ori);
	strcpy_s(p_gyc->message, total_size, ap_message);
	printf("%s : ori\n", ori);
	for (int i = 0; i < 19; i++) {
		*(temp_left + i) = ori[i];
		if (i == 18)	temp_left[i] = '\0';
	}
	printf("%s : temp_left\n", temp_left);
	total_size = strlen(ap_message) + 1;
	p_gyc->message = (char*)realloc(p_gyc->message, total_size);
	strcpy_s(p_gyc->message, total_size, ap_message);
	printf("%s : p_gyc->message 원본 문자열의 왼쪽을 모두 받고 난뒤\n", p_gyc->message);
	for (int i = 18; i < p_gyc->m_max_len; i++)
		*(temp_right + i - 18) = (p_gyc->message)[i];
	printf("%s : temp_right\n", temp_right);
	total_size = BUF_SIZE;
	strcat_s(temp_left, total_size, ins);
	strcat_s(temp_left, total_size, " ");
	strcat_s(temp_left, total_size, temp_right);
	total_size = p_gyc->m_max_len + 1;//p_gyc->m_max_len = strlen(ap_message)+1;에 의해 삽입문자열길이 제외하고 들어가있음
	p_gyc->m_max_len = total_size;
	p_gyc->m_len = total_size;

	memcpy(m_message, temp_left, total_size);
	char* p_message = (char*)malloc(total_size);
	p_message = m_message;
	return p_message;
}
char* SetString_new(struct gycchang* p_gyc, const char* ap_message)
{
	char ori[BUF_SIZE];
	char temp_left[19] = { 0, };//18글자(글자+띄어쓰기용 공백문자)+1바이트(널문자)//after connection, (공백까지포함)(18글자)+strcat으로 붙일 길이(1+21) = 
	char* p_message = NULL;
	p_gyc->m_len = strlen(ap_message) + 1;
	if (p_message == NULL) {
		p_message = (char*)malloc(p_gyc->m_len);
	}
	//기존의 길이보다 더 길게 들어온 문자열 상수일 경우에만 재할당을 하여 cpu 실행속도를 높인다
	if (p_gyc->m_len > p_gyc->m_max_len) {
		free(p_gyc->message);
		p_gyc->m_max_len = p_gyc->m_len;
		p_message = (char*)malloc(p_gyc->m_max_len);//원본 문자열을 만들기위해 p_message에 받은 다음 strcpy를 통해 char형문자열에 복사하여 놓고 이 변수는 변화시켜서 반환
	}
	//더 긴 길이의 문자열상수가 들어왔든, 아닌 경우든 strcpy는 모두 수행해야 하므로 if문 밖에 꺼냈다
	strcpy_s(p_message, p_gyc->m_max_len, ap_message);//strcpy는 두 매개변수의(1차원포인터변수, 배열)(1차원포인터변수, 1차원포인터변수)(1차원배열포인터변수의 *붙인것,1차원char형배열)
	//printf("\n\nSetString_new함수 =>\n%s : p_message, after 처음 할당\n", p_message);
	//printf("문자열간의 복사 memcpy로도 됩니다  =>\n");
	memcpy(p_message, ap_message, p_gyc->m_max_len);
	//printf("SetString_new함수 =>\n%s : p_message, after 처음 할당\n", p_message);

	const char tmp[BUF_SIZE] = "after connection, second(s) has passed.";
	char* r_tmp = method1(&tmp);

	char tmp_array[BUF_SIZE];
	strcpy_s(tmp_array, BUF_SIZE, r_tmp);
	p_gyc->m_count++;
	//삽입문자열에 m_count변수를 사용할 것이다
	//아래의 ins배열의 크기를 1로 해도 잘 실행되는 것을 SetString_ori함수에서 볼 수 있는데
	//크기를 2이상으로 잡아주는 게 맞다
	char ins[6] = { 0, };//1바이트에 정수저장/숫자를 문자열로 바꾼 것을 저장할 배열//-127~128까지 저장가능
						 //정수형 문자열의 정수가 1~5를 넣을 거라서 이걸로 충분+널문자용(1바이트)추가
	char* p;
	//_itoa함수 반환값은 char*형이므로 p라는 char*형 변수에 받는다
	p = _itoa(p_gyc->m_count, ins, 10);//_itoa함수는 CPP와 C모두 작동하는 함수다
	printf("%s: p, %s: ins\n", p, ins);
	//혹은 함수를 사용해서 한다(_itoa함수를 구현한 함수)
	p = IntToBuf(p_gyc->m_count);
	printf("%s: p, %s: ins\n", p, ins);
	int total_size = strlen(temp_left) + 1;
	char* r_ori = (char*)malloc(BUF_SIZE);
	r_ori = method1(&tmp);
	strcpy_s(ori, BUF_SIZE, r_ori);
	//printf("%s : ori\n", ori);
	//printf("%d : strlen(temp_left)\n", strlen(temp_left));
	//printf("%d : total_size at temp_left\n", total_size);
	//printf("strlen(temp_left)의 값이 0인 이유를 모르겠어서 종결조건에 19로 직접 크기 지정\n");
	for (int i = 0; i < 19; i++)
	{
		*(temp_left + i) = ori[i];
		if (i == 18)	*(temp_left + i) = '\0';
	}
	printf("%s : temp_left\n", temp_left);

	//원본 문자열의 왼쪽 부분을 p_message변수에 strcpy로 문자열 복사하고(처음 할당이므로 malloc을 사용)
	//strcpy는 두 매개변수의(1차원포인터변수, 배열)(1차원포인터변수, 1차원포인터변수)(1차원배열포인터변수의 *붙인것,1차원char형배열)
	if (p_message == NULL) {
		total_size = strlen(temp_left) + 1;
		printf("%d : if_첫메세지할당_strlen(temp_left)+1\n", strlen(temp_left) + 1);
		p_message = (char*)malloc(total_size);
		strcpy_s(p_message, total_size, temp_left);
		//strcpy_s(p_message, p_gyc->m_max_len, temp_left);
		printf("%s : p_message after temp_left 복사후\n", p_message);
	}
	//만약 이미 이 주소에 할당이 되어있다면 realloc을 사용해서 strcat으로 붙여넣기를 한다(이때 total_size변수에 temp_left배열의 길이가 들어오므로
	// 이미 이 주소에 다른 값이 저장되어있다해도 충분한 메모리를 가진 메모리로 이동한뒤 이 메모리에 realloc함수는 재할당을 하므로
	// 메모리에 잘려서 들어가는것은 걱정하지 않아도 된다.
	else {
		total_size = strlen(temp_left) + 1;
		printf("%d : else_메세지변수재할당_strlen(temp_left)+1\n", strlen(temp_left) + 1);
		p_message = (char*)realloc(p_message, total_size);
		//strcat_s(p_message, total_size, temp_left);
		strcpy_s(p_message, total_size, temp_left);
		printf("%s : p_message after temp_left 복사후\n", p_message);

	}
	//ins 삽입문자열을 realloc을 통해 재할당 한뒤 문자열 붙여넣기를 하고
	total_size = total_size + 1;//삽입문자열 실제로는 1바이트
	p_message = (char*)realloc(p_message, total_size);
	strcat_s(p_message, total_size, ins);
	printf("%s : p_message after ins 붙여넣기 이후\n", p_message);
	//공백문자 넣기
	total_size += 1;
	p_message = (char*)realloc(p_message, total_size);
	strcat_s(p_message, total_size, " ");
	//temp_right문자열을 realloc을 통해 재할당된 p_message변수에 문자열 붙여넣기를 해서
	char temp_right[22] = {0,};
	p_gyc->m_max_len = strlen(temp_left) + strlen(temp_right) + 1 + 1+1;
	printf("%d : p_gyc->m_max_len\n", p_gyc->m_max_len);
	p_gyc->m_max_len = total_size;
	total_size = strlen(ap_message)+1;
	p_gyc->m_max_len = total_size;
	strcpy_s(p_gyc->message, p_gyc->m_max_len, ap_message);
	printf("%s : p_gyc->message before temp_right를 strcat으로 붙여넣기하기전\n", p_gyc->message);
	for (int i = 18; i < p_gyc->m_max_len; i++)
		*(temp_right + i-18) = *(p_gyc->message+i);
	printf("%s : temp_right\n", temp_right);
	total_size = strlen(temp_left) + strlen(temp_right) + 1 + 1+ 1;
	p_message = (char*)realloc(p_message, total_size);
	strcat_s(p_message, total_size, temp_right);
	printf("%s: p_message 최종 수정후\n", p_message);

	//temp_right와 ins와 공백문자를 한 번에 넣는 방법
	//realloc을 하기전에 total_size를 위에서 언급한 것과 temp_left까지 더한 길이이상으로
	//해준다
	//이렇게 하려면 ins를 strcat으로 붙여넣기하기전에 temp_right초기화를 끝내놓아야 한다
	/*char temp_right[22] = {0,};
	for (int i = 18; i < p_gyc->m_max_len; i++)
		*(temp_right + i) = ori[i];
	printf("%s : temp_right\n", temp_right);
	p_gyc->m_max_len = strlen(temp_left) + strlen(temp_right) + 6 + 1;//6:ins배열, 1: 공백
	total_size = p_gyc->m_max_len;
	p_message = (char*)realloc(p_message, total_size);
	strcat_s(p_message, total_size, ins);
	strcat_s(p_message, total_size, " ");
	strcat_s(p_message, total_size, temp_right);
	printf("%s : p_message수정완료\n", p_message);*/
	//p_message를 반환한다.
	return p_message;
}
int main(int argc, char* argv[])
{
	gycchang gyc;
	p_gyc p_gyc;
	p_gyc = &gyc;
	Init(p_gyc, 1);
	GetInfo(p_gyc);//Init한 구조체변수가 제대로 할당되었는지 확인
	const char tmp_message[BUF_SIZE] = "after connection, second(s) has passed.";
	const char* p_tmp_message = tmp_message;
	char* r_SetString_ori = NULL;
	for (int i = 0; i < 5; i++) {
		r_SetString_ori = SetString_ori(p_gyc, p_tmp_message);
		printf("%s : r_SetString_ori 반환값\n", r_SetString_ori);
	}
	char* r_SetString_new = NULL;
	for (int i = 0; i < 5; i++) {
		r_SetString_new = SetString_new(p_gyc, p_tmp_message);
		printf("%s : r_SetString_new 반환값\n", r_SetString_new);
	}
		

	return 0;
}