package loopexample;

public class ForExample {

	public static void main(String[] args) {

		
		int sum = 0;
		for(int num = 1 ; num <= 10 ; num++)
		{
			sum += num;
		}
		System.out.println("1부터 10까지의 합은 "+sum+"입니다.");
		
		System.out.println();
		
		int dan;
		int time;
		
		for(dan = 2 ; dan<= 9; dan++)
		{
			for(time = 1; time<=9 ; time++)
			{
				System.out.println(dan+"X"+time+"="+dan*time);
			}
			System.out.println();
		}
		
	}

}
