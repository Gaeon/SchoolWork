package ifexample;

public class IfExample2 {

	public static void main(String[] args) {

		int age = 3;
		int charge;
		if(age > 19)
		{
			System.out.println("�����Դϴ�");
			charge = 10000;
		}
		else if(age > 13)
		{
			System.out.println("�߰����л��Դϴ�");
			charge = 5000;
		}
		else if(age > 7)
		{
			System.out.println("�ʵ��л��Դϴ�");
			charge = 2500;
		}
		else
		{
			System.out.println("�����оƵ��Դϴ�");
			charge = 0;
		}
		System.out.println("������ "+charge+"�� �Դϴ�.");

	}

}