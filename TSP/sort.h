//�����㷨
#ifndef SORT_H
#define SORT_H

/**----------------------------------------------------------------------------------------------------- 
 * FUNCTION: The integers to be sorted are stored in keyArray[first] ... keyArray[last].
 *           The index with smallest key value is assigned to sortedArray[first], and so on.
 *           The elements of keyArray don't change      
 * INPUT   : keyArray -- The integers to be sorted    
 *           sortedArray -- The sorted index
 *           first -- The first element to be sorted.
 *           last -- The last element to be sorted.
 *           namely, the range to be sorted is [sortedArray[first], ... , sortedArray[last]]                     
 ------------------------------------------------------------------------------------------------------*/ 
template <typename Comparable>
void sortNondecreasing( const Comparable keyArray[], int sortedArray[], int first, int last )	
{
	int j, k;
	Comparable x;
	for( int i = first; i < last; i++ ) 
	{
		k = i;
		x = keyArray[sortedArray[i]];
		for( j = i + 1; j <= last; j++ ) 
			if( keyArray[sortedArray[j]] < x ) 
			{
				k = j;                          //kΪi֮����СԪ�ص����
				x = keyArray[sortedArray[j]];   //xΪ��СԪ��
			}
		j = sortedArray[k]; //����Ԫ��ֵ
		sortedArray[k] = sortedArray[i];
		sortedArray[i] = j;  
	}
}
//--------------------------------------------------------------------------------------------------------
/* FUNCTION: The integers to be sorted are stored in keyArray[first] ... keyArray[last].
 *           The index with largest key value is assigned to sortedArray[first], and so on.
 *           The elements of keyArray don't change      
 * INPUT   : keyArray -- The integers to be sorted    
 *           sortedArray -- The sorted index
 *           first -- The first element to be sorted.
 *           last -- The last element to be sorted.
 *           namely, the range to be sorted is [sortedArray[first], ... , sortedArray[last]]                     
 ---------------------------------------------------------------------------------------------------------*/ 
template <typename Comparable>
void sortNonincreasing( const Comparable keyArray[], int sortedArray[], int first, int last )	
{
	int j, k;
	Comparable x;
	for( int i = first; i < last; i++ ) 
	{
		k = i;
		x = keyArray[sortedArray[i]];
		for( j = i+1; j <= last; j++ ) 
			if( keyArray[sortedArray[j]] > x ) 
			{
				k = j;                          //kΪi֮�����Ԫ�ص����
				x = keyArray[sortedArray[j]];   //xΪ���Ԫ��
			}
		j = sortedArray[k];//����Ԫ��ֵ
		sortedArray[k] = sortedArray[i];
		sortedArray[i] = j;
	}
}

#endif /* SORT_H */