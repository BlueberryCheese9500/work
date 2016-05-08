import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Huffman 
{
	public static void main(String[] args) 
	{
		String[] filename = new String[3]; // 읽을 파일 명
		filename[0] = "huffman_test1.txt"; 
		filename[1] = "huffman_test2.txt";
		filename[2] = "huffman_test3.txt";
		String path = Huffman.class.getResource(".").getPath(); // 클래스 실행경로
		ArrayList<CharWithFrequency> huffmanlist = null; // 트리를 만들 글자리스트
		
		try 
		{	
			for(int k=0;k<filename.length;k++) 
			{
				// 현재 클래스 실행경로의 파일을 읽는 리더객체 생성
				FileReader filereader = new FileReader(path+filename[k]); 
				System.out.println("file name : "+filename[k]+"\n");
				// 파일의 글자수 마다 빈도수를 측정하여 리스트로 저장
				huffmanlist = new MakeFrequencyList(filereader).MakeFrequencyList(); 
				// 만들어진 리스트를 빈도수대로 오름차순 퀵소트정렬
				new QuickSort(huffmanlist, huffmanlist.size()).quickSort(huffmanlist, 0, huffmanlist.size()-1);

				System.out.println("병합 과정\n");
				for(int i=0;i<huffmanlist.size();i++)
					System.out.print(huffmanlist.get(i).charecter+""+huffmanlist.get(i).frequency+"\t");
				System.out.println("");
				// 허프만 트리 생성
				new MakeHuffmanTree(huffmanlist).maketree();
				
				// 파일 별 구분선 출력
				System.out.println("\n\n================================================="
						+ "=========================\n");
				huffmanlist.removeAll(huffmanlist); // 사용한 리스트 비움
				filereader.close(); // 사용한 파일 닫기
			}
		} 
		catch (IOException e) 
		{
			System.out.println("파일 읽기 실패");
			e.printStackTrace();
			return;
		}
	}
}

class CharWithFrequency
{
	char charecter = ' '; // 글자
	int frequency = 0;    // 출현 빈도수
	String nodeType;      // 노드의  타입, 중간 노드/리프노드
	String code = "";     // 부여될 코드 
	CharWithFrequency leftchild = null; // 왼쪽 자식 노드
	CharWithFrequency rightchild = null;// 오른쪽 자식 노드
	// 리프노드 생성을 위한 생성자
	public CharWithFrequency(char charecter, int frequency)
	{// 글자와 빈도수를 입력받아 리프노드로 생성
		this.charecter = charecter;
		this.frequency = frequency;
		nodeType = "leaf";
	}
	// 리프노드를 묶을 미드노드 생성자
	public CharWithFrequency(int weight)
	{// 합한 가중치를 받아 미드노드로 생성
		nodeType = "mid";
		this.frequency = weight;
	}
}
