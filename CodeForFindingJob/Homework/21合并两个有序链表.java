// 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

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
    public ListNode mergeTwoLists(ListNode list1, ListNode list2) {
        if (list1 == null) return list2;
        if (list2 == null) return list1;
        ListNode result = new ListNode();
        ListNode currentListEnd = new ListNode();
        ListNode current1Node = list1;
        ListNode current2Node = list2;
        if (current1Node.val < current2Node.val) {
            result = current1Node;
            current1Node = current1Node.next;
        } else {
            result = current2Node;
            current2Node = current2Node.next;
        }
        currentListEnd = result;
        while (current2Node != null && current1Node != null) {
            ListNode newAddedNode = new ListNode();
            if (current1Node.val < current2Node.val) {
                newAddedNode = current1Node;
                current1Node = current1Node.next;
            } else {
                newAddedNode = current2Node;
                current2Node = current2Node.next;
            }
            currentListEnd.next = newAddedNode;
            currentListEnd = newAddedNode;
        }
        if(current1Node==null)
            currentListEnd.next = current2Node;
        else
            currentListEnd.next = current1Node;
        return result;
    }
}