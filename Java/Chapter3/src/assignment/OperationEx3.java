package assignment;

public class OperationEx3 {

	public static void main(String[] args) {
		int num1 = 10;
		int i = 2;
		
		boolean value = ((num1+=10)<10 && (i+=2)<10);
		System.out.println(value);
		System.out.println(num1);
		System.out.println(i);
		//앞의 항이 false이므로 뒤의 항의 연산이 이루어지지 않음
		
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
		//앞의 항이 true이므로 뒤의 항의 연산이 이루어짐
	}
}
