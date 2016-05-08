import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class MakeFrequencyList 
{
	FileReader filereader = null; // 읽을 파일
	private ArrayList<CharWithFrequency> ret; // 반환할 리스트
	
	public MakeFrequencyList(FileReader filereader)
	{
		ret = new ArrayList<CharWithFrequency>();
		this.filereader = filereader;
	}

	public ArrayList<CharWithFrequency> MakeFrequencyList()
	{
		char buf[] = new char[1];
		int i = -1;
		try 
		{	//파일을 한 바이트씩 읽어서
			while(filereader.read(buf)!=-1)
			{// 읽은 문자열이 기존에 없던 문자열이면  리스트에 추가
				if((i=listRedundentCheck(buf[0]))==-1) 
					ret.add(new CharWithFrequency(buf[0],1));
				else// 기존에 있던 거라면 빈도수 추가
					ret.get(i).frequency++;
			}
			filereader.close();// 사용 끝난 파일 닫음
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
		return ret;
	}
	// 중복체크
	public int listRedundentCheck(char c)
	{// 현재까지 만들어진 리스트 모두 검사해서 입력받은 데이터와 동일한게 있으면
		for(int i = 0 ;i < ret.size(); i++)
			if(c == ret.get(i).charecter)
				return i;	// 인덱스를 넘기고
		
		return -1; // 아닐 경우 -1 리턴
	}
}
