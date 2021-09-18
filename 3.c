#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
typedef struct node* p_node;
typedef struct node {
	int value;
	node* p_next;
}node;
typedef struct gycchang {
	int m_len;
	int m_max_len;
	int m_count;//1�ʰ� ���������� �����ϸ鼭 ������ų �������
	char* message;
}gycchang;
typedef struct gycchang* p_gyc;
#define BUF_SIZE 44
void Init(void* const p, char flag);
char* SetString_ori(struct gycchang* p_gyc, const char* ap_message);//���� ������ strcat���� ���ڿ� �ٿ��ֱ⸦ ���� ��ȯ
char* SetString_new(struct gycchang* p_gyc, const char* ap_message);//���ο� ������ strcat���� ���ڿ��ٿ��ֱ⸦ ���� ��ȯ
void Init(void* const p, char flag)
{
	if (flag) {
		((p_gyc)p)->m_len = 1;
		((p_gyc)p)->m_max_len = 1;
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
	char p_tmp_array = (char*)malloc(BUF_SIZE);
	char tmp_array[BUF_SIZE] = { 0, };
	strcpy_s(tmp_array, BUF_SIZE, *ap_str);
	p_tmp_array = tmp_array;
	return p_tmp_array;
}
//�ι��ڸ� �������� �ʰ� �ι��ڸ� �迭�� ���޹��� �Լ����� �ٿ��� printf���ִ� �ڵ�
//char*�� ��ȯ�̿��� char�� �迭�� ��ȯ�ص� �����۵��մϴ�
char* method2(char(*ptr)[BUF_SIZE], int str_len)
{
	//Ȯ��(�ι��ڸ� �����ϰ� �Ѿ�͵� �����۵��ϴ��� Ȯ���Ϸ��� int�� ������ �Ű������� �޾Ƽ� Ȯ���غ� ���̴�)
	printf("str_len %d = strlen(*ptr) %d\n", str_len, strlen(*ptr));
	//�ι��ڸ� ���̴� �۾�
	//*ptr = *(ptr+0) : ���ڿ� �����ּ�
	//[BUF_SIZE-1] : ������ �ε����� �ι��ڸ� �־��ش�
	(*ptr)[BUF_SIZE - 1] = '\0';
	printf("%s : �ι��ڸ� ���� ���ڿ��� ����ؾ� �����۵��մϴ�\n", *ptr);

}
char* IntToBuf(int i)
{
	char* Buf = (char*)malloc(1);
	sprintf(Buf, "%d", i);
	return Buf;
}
char* SetString_ori(struct gycchang* p_gyc, const char* ap_message)
{
	char*r_tmp;
	//�����͸� �޾Ƽ� 
	char ori[BUF_SIZE];
	char temp_left[41] = {0,};//18����(����+����� ���鹮��)//after connection, (�����������)(18����)+strcat���� ���� ����(1+21)+�ι��ڿ�(1����Ʈ) = 41
	char temp_right[22];//21����+1����Ʈ(�ι���)//second(s) has passed.(21����)
	char ins[1];//���ڸ� ���ڿ��� �ٲ� ���� ������ �迭//-127~128���� ���尡��//������ ���ڿ��� ������ 1~5�� ���� �Ŷ� �̰ɷ� ���
	int total_size = strlen(temp_left) + 1;
	//const int limit = BUF_SIZE;
	char m_message[BUF_SIZE];

	if (p_gyc == NULL) {
		p_gyc = (struct gycchang*)malloc(sizeof(gycchang));
		total_size = strlen(ap_message) + 1;//<=44
		p_gyc->message = (char*)malloc(total_size);
	}
	else {
		total_size = streln(ap_message) + 1;
		p_gyc->message = (char*)realloc(p_gyc->message,total_size);
	}
	p_gyc->m_max_len=total_size;
	p_gyc->m_len = total_size;
	for (int i = 0; i < 19; i++) {
		*(temp_left + i) = ori[i];
		if (i == 18)	temp_left[i] = '\0';
	}
	for (int i = 18; i < p_gyc->m_max_len; i++)
		*(temp_right + i - 18) = ori[i];
	strcat_s(temp_left, 1, ins);
	strcat_s(temp_left, 1, " ");
	strcat_s(temp_left, p_gyc->m_max_len - 18, temp_right);
	total_size = p_gyc->m_max_len + 1;//p_gyc->m_max_len = strlen(ap_message)+1;�� ���� ���Թ��ڿ����� �����ϰ� ������
	p_gyc->m_max_len = total_size;
	p_gyc->m_len = total_size;

	memcpy(m_message, temp_left, total_size);
	return m_message;
}
char* SetString_new(struct gycchang* p_gyc, const char* ap_message)
{
	char* r_tmp;
	//�����͸� �޾Ƽ� 
	char ori[BUF_SIZE];
	char temp_left[19] = { 0, };//18����(����+����� ���鹮��)+1����Ʈ(�ι���)//after connection, (�����������)(18����)+strcat���� ���� ����(1+21) = 
	char* p_message = NULL;
	p_gyc->m_len = strlen(ap_message) + 1;
	if (p_message == NULL) {
		p_message = (char*)malloc(p_gyc->m_len);
	}
	//������ ���̺��� �� ��� ���� ���ڿ� ����� ��쿡�� ���Ҵ��� �Ͽ� cpu ����ӵ��� ���δ�
	if (p_gyc->m_len > p_gyc->m_max_len) {
		free(p_gyc->message);
		p_gyc->m_max_len = p_gyc->m_len;
		p_message = (char*)malloc(p_gyc->m_max_len);//���� ���ڿ��� ��������� p_message�� ���� ���� strcpy�� ���� char�����ڿ��� �����Ͽ� ���� �� ������ ��ȭ���Ѽ� ��ȯ
	}
	//�� �� ������ ���ڿ������ ���Ե�, �ƴ� ���� strcpy�� ��� �����ؾ� �ϹǷ� if�� �ۿ� ���´�
	strcpy_s(p_message, p_gyc->m_max_len, ap_message);//strcpy�� �� �Ű�������(1���������ͺ���, �迭)(1���������ͺ���, 1���������ͺ���)(1�����迭�����ͺ����� *���ΰ�,1����char���迭)
	

	const char tmp[BUF_SIZE] = "after connection, second(s) has passed.";
	char* r_tmp = method1(&tmp);

	char tmp_array[BUF_SIZE];
	strcpy_s(tmp_array, BUF_SIZE, r_tmp);
	p_gyc->m_count++;
	//���Թ��ڿ��� m_count������ ����� ���̴�
	char ins[1] = { 0, };
	char* p;
	//_itoa�Լ� ��ȯ���� char*���̹Ƿ� p��� char*�� ������ �޴´�
	p = _itoa(p_gyc->m_count, ins, 10);//_itoa�Լ��� CPP�� C��� �۵��ϴ� �Լ���
	printf("%s: p, %s: ins\n", p, ins);
	//Ȥ�� �Լ��� ����ؼ� �Ѵ�(_itoa�Լ��� ������ �Լ�)
	IntToBuf(p_gyc->m_count);
	printf("%s: p, %s: ins\n", p, ins);
	int total_size = strlen(temp_left) + 1;
	for (int i = 0; i < total_size; i++)
		*(temp_left + i) = ori[i];
	printf("%s : temp_left\n", temp_left);

	//���� ���ڿ��� ���� �κ��� p_message������ strcpy�� ���ڿ� �����ϰ�(ó�� �Ҵ��̹Ƿ� malloc�� ���)
	//strcpy�� �� �Ű�������(1���������ͺ���, �迭)(1���������ͺ���, 1���������ͺ���)(1�����迭�����ͺ����� *���ΰ�,1����char���迭)
	if (p_message == NULL) {
		total_size = strlen(temp_left) + 1;
		p_message = (char*)malloc(total_size);
		strcpy_s(p_message, p_gyc->m_max_len, ap_message);
	}
	//���� �̹� �� �ּҿ� �Ҵ��� �Ǿ��ִٸ� realloc�� ����ؼ� strcat���� �ٿ��ֱ⸦ �Ѵ�(�̶� total_size������ temp_left�迭�� ���̰� �����Ƿ�
	// �̹� �� �ּҿ� �ٸ� ���� ����Ǿ��ִ��ص� ����� �޸𸮸� ���� �޸𸮷� �̵��ѵ� �� �޸𸮿� realloc�Լ��� ���Ҵ��� �ϹǷ�
	// �޸𸮿� �߷��� ���°��� �������� �ʾƵ� �ȴ�.
	else {
		total_size = strlen(temp_left) + 1;
		p_message = (char*)realloc(p_message, total_size);
		strcat_s(p_message, total_size, temp_left);
	}
	//ins ���Թ��ڿ��� realloc�� ���� ���Ҵ� �ѵ� ���ڿ� �ٿ��ֱ⸦ �ϰ�
	total_size = total_size + 1;
	p_message = (char*)realloc(p_message, total_size);
	strcat_s(p_message, total_size, ins);
	//���鹮�� �ֱ�
	total_size += 1;
	p_message = (char*)realloc(p_message, total_size);
	strcat_s(p_message, total_size, " ");
	//temp_right���ڿ��� realloc�� ���� ���Ҵ�� p_message������ ���ڿ� �ٿ��ֱ⸦ �ؼ�
	char temp_right[22] = {0,};
	for (int i = 18; i < p_gyc->m_max_len; i++)
		*(temp_right + i) = ori[i];
	printf("%s : temp_right\n", temp_right);
	total_size += strlen(temp_right);
	p_message = (char*)realloc(p_message, total_size);
	strcat_s(p_message, total_size, temp_right);
	printf("%s: p_message ���� ������\n", p_message);
	//p_message�� ��ȯ�Ѵ�.
	return p_message;
}
int main(int argc, char* argv[])
{
	gycchang gyc;
	p_gyc p_gyc;
	p_gyc = &gyc;
	Init(p_gyc, 1);
	GetInfo(p_gyc);//Init�� ����ü������ ����� �Ҵ�Ǿ����� Ȯ��
	const char tmp_message[BUF_SIZE] = "after connection, second(s) has passed.";
	const char* p_tmp_message = tmp_message;
	char* r_SetString_ori = NULL;
	for (int i = 0; i < 5; i++) {
		r_SetString_ori = SetString_ori(p_gyc, p_tmp_message);
	}
	char* r_SetString_new = NULL;
	for(int i=0;i<5;i++)
		r_SetString_new = SetString_new(p_gyc, p_tmp_message);
	return 0;
}