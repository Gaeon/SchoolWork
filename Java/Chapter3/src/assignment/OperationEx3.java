package assignment;

public class OperationEx3 {

	public static void main(String[] args) {
		int num1 = 10;
		int i = 2;
		
		boolean value = ((num1+=10)<10 && (i+=2)<10);
		System.out.println(value);
		System.out.println(num1);
		System.out.println(i);
		//���� ���� false�̹Ƿ� ���� ���� ������ �̷������ ����
		
		num1 = 10;
		i = 2;
		
		boolean value2 = ((num1+=10)<10 || (i+=2)<10);
		System.out.println(value2);
		System.out.println(num1);
		System.out.println(i);
		
		num1 = 10;
		i = 2;
		
		boolean value3 = ((num1+=10)>10 && (i+=2)<10);
		System.out.println(value3);
		System.out.println(num1);
		System.out.println(i);
		//���� ���� true�̹Ƿ� ���� ���� ������ �̷����
	}
}