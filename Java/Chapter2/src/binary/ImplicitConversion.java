package binary;

public class ImplicitConversion {

	public static void main(String[] args) {
		
		//적은 메모리에서 큰 메모리로 변환 => 묵시적형변환/자동형변환 가능
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
