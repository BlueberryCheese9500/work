import java.util.ArrayList;

public class QuickSort 
{
	private	ArrayList<CharWithFrequency> a = null;
	private int aSize ;

	public QuickSort(ArrayList<CharWithFrequency> charList, int n)
	{  //생성자 함수, 정렬할 데이터를 배열 a 에 받음
		a = charList;                              //임시 배열 b 를 동적으로 생성
		aSize = n;
	}

	void quickSort(ArrayList<CharWithFrequency> arr, int left, int right) 
	{
		int index = partition(arr, left, right);

		if (left < index - 1)
			quickSort(arr, left, index - 1);

		if (index < right)	
			quickSort(arr, index, right);
	}
	
	int partition(ArrayList<CharWithFrequency> arr, int left, int right) 
	{
		int i = left, j = right;
		int pivot = arr.get((left + right) / 2).frequency;
		
		while (i <= j) 
		{
			while (arr.get(i).frequency < pivot) i++;
			while (arr.get(j).frequency > pivot) j--;
			if (i <= j) 
			{	
				swapCharWithFrequency(arr,i, j);
				i++;
				j--;
			}
		};
		return i;
	}
	
	public void swapCharWithFrequency
	(ArrayList<CharWithFrequency> a, int i, int j)
	{
		int frequency = a.get(i).frequency;
		char charecter = a.get(i).charecter;
		String nodeTyep = a.get(i).nodeType;
		CharWithFrequency leftchild = a.get(i).leftchild;
		CharWithFrequency rightchild = a.get(i).rightchild;
		a.get(i).frequency = a.get(j).frequency;
		a.get(i).charecter = a.get(j).charecter;
		a.get(i).leftchild = a.get(j).leftchild;
		a.get(i).rightchild = a.get(j).rightchild;
		a.get(i).nodeType = a.get(j).nodeType;
		
		a.get(j).charecter = charecter;
		a.get(j).frequency = frequency;
		a.get(j).leftchild = leftchild;
		a.get(j).rightchild = rightchild;
		a.get(j).nodeType = nodeTyep;
	}
}
