package loopexample;

public class BreakExample {

	public static void main(String[] args) {

		int sum = 0;
		int num = 1;
		while(true)
		{
			sum += num;
			if(sum > 100)
			{
				break;
			}
			num++;
		}
		System.out.println(sum);
		System.out.println(num); //14 까지 더했을 때 sum이 100을 넘음
		
	}
}
