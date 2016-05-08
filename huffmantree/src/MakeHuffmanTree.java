import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class MakeHuffmanTree 
{
	private ArrayList<CharWithFrequency> huffmanlist;
	private Queue<CharWithFrequency> queue;
	private CharWithFrequency headNode;
	public MakeHuffmanTree(ArrayList<CharWithFrequency> huffmanlist)
	{
		this.huffmanlist = huffmanlist;
		queue =  new LinkedList<CharWithFrequency>();
		queue.addAll(huffmanlist);
	}

	public void maketree() // 트리 생성
	{// 임시로 노드들을 저장할 큐를 생성
		Queue<CharWithFrequency> result =  new LinkedList<CharWithFrequency>();
		do
		{
			CharWithFrequency leftchild = queue.poll(); //가장 작은 2개의 노드를 꺼낸다
			CharWithFrequency rightchild = queue.poll();
			// 가중치 합을 가진 부모 노드 생성
			CharWithFrequency midNode = new CharWithFrequency(leftchild.frequency+rightchild.frequency);
			midNode.leftchild = leftchild;  // 트리를 만든다
			midNode.rightchild = rightchild;
			
			while(!queue.isEmpty()) // 남은 노드들 다 저장
				result.add(queue.poll());
			result.add(midNode); // 결과 큐에 저장
			sortQueue(result); // 결과큐 정렬
				
			queue.removeAll(queue); // 기존에 있던 큐를 다 비우고 정렬된 결과를 집어넣음
			queue.addAll(result);	 		
			result.removeAll(result); // result를 다 비움 			
		}while(queue.size()>=2);  // 마지막 노드가 두개 남을 때까지
		
		headNode = queue.peek(); // 헤드 노드에 마지막 남은 루트 노드를 대입
		// 결과 구분 표시줄 출력
		System.out.println("\n-----------------------------"
				+ "---------------------------------------------\n");
		System.out.println("중위 순회 결과");
		System.out.print("char\t");
		inorderPrint(headNode);  // 중위 순회하면서 코드 부여 및 글자 출력
		System.out.println("\n"); 
		System.out.print("freq\t");
		inorderPrint2(headNode); // 빈도수 중위 순회로 출력
		System.out.println("\n");
		System.out.print("code\t");
		inorderPrint3(headNode); // 코드번호를 중위 순회로 출력
	}
	// 중위 순회하면서 코드 부여 및 출력
	public void inorderPrint(CharWithFrequency head)
	{	
		if(head == null) 
			return;

		if(head.leftchild!=null)
			head.leftchild.code=head.code+"0"; //왼쪽자식에 0을 부여
		inorderPrint(head.leftchild);
		System.out.print(head.charecter+"\t"); // 문자 출력
		if(head.rightchild!=null)
			head.rightchild.code=head.code+"1"; //오른쪽 자식에 1을 부여
		inorderPrint(head.rightchild);
	}
	// 중위순회 빈도수 출력
	public void inorderPrint2(CharWithFrequency head)
	{	
		if(head == null) 
			return;

		inorderPrint2(head.leftchild);
		System.out.print(head.frequency+"\t");
		inorderPrint2(head.rightchild);
	}	
	// 중위순회 코드 출력
	public void inorderPrint3(CharWithFrequency head)
	{	
		if(head == null) 
			return;

		inorderPrint3(head.leftchild);
		System.out.print(head.code+"\t");
		inorderPrint3(head.rightchild);
	}
	// 큐를 리스트에 담아서 정렬 후 정렬 된 큐로 만들어줌
	public void sortQueue(Queue<CharWithFrequency> target)
	{	
		ArrayList<CharWithFrequency> temp = new ArrayList<CharWithFrequency>();
		temp.addAll(target); //임시 리스트에 큐에 있는 인자를 다 넣고
		// 퀵 정렬
		new QuickSort(temp, temp.size()).quickSort(temp, 0, temp.size()-1); 		
		
		System.out.println("");
		for(int k=0;k<temp.size();k++)
		{
			if(temp.get(k).nodeType.equals("mid")) // 미드 노드일 경우 노드 타입을 풀력
				System.out.print(temp.get(k).nodeType+temp.get(k).frequency+"\t");
			else  // 리프노드일 경우 문자를 출력
			 System.out.print(temp.get(k).charecter+""+temp.get(k).frequency+"\t");
			
		}
		System.out.println("");
		target.removeAll(target); // 큐를 비우고
		target.addAll(temp); // 정렬된 값으로 채움
	}
}
