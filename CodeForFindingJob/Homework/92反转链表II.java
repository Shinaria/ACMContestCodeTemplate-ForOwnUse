// 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。 

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
    public ListNode reverseBetween(ListNode head, int left, int right) {
        if(left>=right)
            return head;
        ListNode targetStart = null;
        ListNode rightEdge = null;
        ListNode leftEdge = null;
        ListNode currentNode = head;
        ListNode previousNode = null;
        for (int no = 1; no <= right; no++) {
            ListNode nextNode = currentNode.next;
            if (no == left) {
                leftEdge = previousNode;
                targetStart = currentNode;
            }
            else if (no == right) {
                rightEdge = nextNode;
                currentNode.next = previousNode;
                if (leftEdge != null) {
                    leftEdge.next = currentNode;
                }
                else {
                    head = currentNode;
                }
            }
            else if (no >left) {
                currentNode.next = previousNode;
            }
            previousNode = currentNode;
            currentNode = nextNode;
        }
        if(targetStart!=null)
            targetStart.next = rightEdge;
        return head;
    }
}