package binary;

public class ImplicitConversion {

	public static void main(String[] args) {
		
		//���� �޸𸮿��� ū �޸𸮷� ��ȯ => ����������ȯ/�ڵ�����ȯ ����
		byte bNum = 10;
		int num = bNum;
		
		System.out.println(num);
		
		long lNum = 10;
		float fNum = lNum;
		
		System.out.println(fNum);
		
		double dNum = fNum + num;
		System.out.println(dNum);
	}

}
