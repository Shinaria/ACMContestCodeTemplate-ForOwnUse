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

// 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。 

import java.util.ArrayDeque;
import java.util.Deque;
class Solution {
    public ListNode reverseList(ListNode head) {
        if(head==null)
        {
            return null;
        }
            Deque<ListNode> stack = new ArrayDeque<>();
            ListNode currentNode = head;
                stack.push(head);
            while(currentNode.next!=null)
            {
                currentNode = currentNode.next;
                stack.push(currentNode);
            }
            ListNode result = new ListNode();
            if(!stack.isEmpty())
            {
                result = stack.pop();
                currentNode = result;
            }
            while(!stack.isEmpty())
            {
                ListNode newNode = stack.pop();
                currentNode.next = newNode;
                currentNode = newNode;
            }
        currentNode.next = null;
        return result;
    }
}