package binary;

public class Constant {

	public static void main(String[] args) {

		final int MAX_NUM = 100;
		final double PI = 3.14;
		
		//MAX_NUM = 3;	final�� ���� => ��� => �ٲ� �� ����
		
		System.out.println(MAX_NUM);
		System.out.println(PI);
		
		final int STUDENT_NUM = 30;
		int num = 0;
		if(num != STUDENT_NUM) {
			num++;
		}
		else {
			System.out.println(num);
		}
		
		System.out.println(num);
		System.out.println(STUDENT_NUM);
		
	}

}