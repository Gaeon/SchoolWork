package binary;

public class ExplicitCoversion {

	public static void main(String[] args) {
		//작은 데이터 값을 큰 데이터 값으로 넣을 때 => 명시적 형변환
		//데이터 손실이 있을 수 있음
		int iNum = 1000;
		byte bNum = (byte)iNum;
		
		System.out.println(iNum);
		System.out.println(bNum);
		
		double dNum = 3.14;
		iNum = (int)dNum;
		System.out.println(dNum);
		System.out.println(iNum);
		
		float fNum = 0.9F;
		int num1 = (int)fNum + (int)dNum;
		int num2 = (int)(fNum+dNum);
		System.out.println(num1);
		System.out.println(num2);
	}

}
