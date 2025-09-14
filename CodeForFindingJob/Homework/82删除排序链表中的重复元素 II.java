// 给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {

    ListNode GetLastEqualNode(ListNode node)
    {//寻找和自己相同值的最远节点
        if(node==null) return null;//null判断
        ListNode currentNode = node;
        while(currentNode!=null&&currentNode.next!=null)
        {
            ListNode nextNode = currentNode.next;
            if(nextNode.val!=currentNode.val)//找到了第一个和自己不同值的节点, 直接返回前一个
                return currentNode;
            else
                currentNode=nextNode;
        }
        return currentNode;//遍历到最后有null,返回前一个
    }

    public ListNode deleteDuplicates(ListNode head) {
        //由于给定的头部节点可能会出现重复, 所以需要寻找真实返回的头部
        ListNode realHead = head;
        while(realHead!=null&&realHead!=GetLastEqualNode(realHead))
        {//发现了和头部相同的非本身的节点, 真实头部是下一个节点
            realHead=GetLastEqualNode(realHead).next;
        }
        if(realHead==null) return null;
        ListNode currentNode = realHead.next;
        ListNode previousNode = realHead;
        //头部已经去重, 接下来遍历然后删除
        while(currentNode!=null&&currentNode.next!=null)
        {
            ListNode lastEqualNode = GetLastEqualNode(currentNode);//寻找最远的和自己相同的节点
            if(lastEqualNode==currentNode)
            {//最远的相同节点是自己
                previousNode = currentNode;
                currentNode = currentNode.next;
            }
            else
            {//最远的相同结点不是自己
                previousNode.next = lastEqualNode.next;
                currentNode = lastEqualNode.next;
            }
        }
        return realHead;
    }
}